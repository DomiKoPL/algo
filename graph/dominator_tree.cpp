
struct DomTree {
    static const int N = 2e5 + 7;
    vi graph[N], rgraph[N];
    vi tree[N], bucket[N];
    int sdom[N], idom[N], label[N], par[N];
    int nr[N], rnr[N], TIME = 0;
    int dsu[N];
    int n;
    DomTree(int n) : n(n) {
        FOR(i, 0, n + 1) {
            nr[i] = 0;
        }
    }
    void addEdge(int u, int v) {
        graph[u].push_back(v);
    }
    int Find(int u, int x = 0) {
        if(u == dsu[u]) {
            return x ? -1 : u;
        }
        int v = Find(dsu[u], x + 1);
        if(v < 0) {
            return u; 
        }
        if(sdom[label[dsu[u]]] < sdom[label[u]]) {
            label[u] = label[dsu[u]];
        }
        dsu[u] = v;
        return x ? v : label[u];
    }
    void Union(int u, int v) {
        dsu[v] = u;
    }
    void preDFS(int u) {
        nr[u] = ++TIME;
        rnr[TIME] = u;
        label[TIME] = sdom[TIME] = dsu[TIME] = TIME;
        for(auto& v : graph[u]) {
            if(!nr[v]) {
                preDFS(v);
                par[nr[v]] = nr[u];
            }
            rgraph[nr[v]].push_back(nr[u]);
        }
    }
    void build(int s) {
        FOR(i, 0, TIME) {
            rgraph[i].clear();
            bucket[i].clear();
            tree[i].clear();
        }
        TIME = 0;
        preDFS(s);
        n = TIME;   
        FORR(i, n, 1) {
            for(auto& v : rgraph[i]) {
                sdom[i] = min(sdom[i], sdom[Find(v)]);
            }
            if(i > 1) {
                bucket[sdom[i]].push_back(i);
            }
            for(auto& w : bucket[i]) {
                int v = Find(w);
                if(sdom[v] == sdom[w]) {
                    idom[w] = sdom[w];
                } else {
                    idom[w] = v;
                }
                
            }

            if(i > 1) {
                Union(par[i], i);
            }
        }

        FOR(i, 2, n + 1) {
            if(idom[i] != sdom[i]) {
                idom[i] = idom[idom[i]];
            }
            tree[rnr[i]].push_back(rnr[idom[i]]);
            tree[rnr[idom[i]]].push_back(rnr[i]);
        }
    }

    vi res;
    void dfs(int u, int p, int g) {
        bool leaf = true;
        for(auto& v : tree[u]) if(v != p) {
            leaf = false;
            dfs(v, u, g + 1);
        }

        if(!leaf and g) {
            res.push_back(u);
        }
    }

    vi calcNotTrivialDoms(int s) {
        build(s);
        res.clear();
        dfs(s, -1, 0);
        return res;
    };
};