struct Dinic {
    static const int MAXN= 2e5 + 7;
    const int INF = 1e9 + 7;

    struct Edge{
        int from, to, cap, flow;
        Edge() {}
        Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
    };

    vector<Edge> edges;
    vector<int> G[MAXN];
    bitset<MAXN> vis;
    int d[MAXN], cur[MAXN];

    void init(int n)
    {
        for(int i = 0; i <= n; i++) G[i].clear();
        edges.clear();
    }

    void addEdge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        int t_m = edges.size();
        G[from].push_back(t_m - 2);
        G[to].push_back(t_m - 1);
    }

    bool BFS(int s, int t) {
        vis.reset();
        queue<int> Q;
        Q.push(s);
        d[s] = 0; vis[s] = 1;
        while(Q.size()) {
            int x = Q.front(); Q.pop();
            for(int i = 0; i < G[x].size(); i++) {
                Edge& e = edges[G[x][i]];
                if(!vis[e.to] and e.cap > e.flow) {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x, int a, int s, int t) {
        if(x == t or a == 0) return a;
        int flow = 0, _f;
        for(int& i = cur[x]; i < G[x].size(); i++) {
            Edge& e = edges[G[x][i]];
            if(d[x] + 1 == d[e.to] and (_f = DFS(e.to, min(a, e.cap - e.flow), s, t)) > 0) {
                e.flow += _f;
                edges[G[x][i] ^ 1].flow -= _f;
                flow += _f;
                a -= _f;
                if(a == 0) {
                    break;
                }
            }
        }
        return flow;
    }

    int maxFlow(int s, int t) {
        int flow = 0;
        while(BFS(s, t)) {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF, s, t);
        }
        return flow;
    }
}flow;