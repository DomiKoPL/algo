template <int N> struct LCA {
    vector<int> graph[N];
    int nr[N], pre[N], fir[N];
    int TIME = 0, id = 0;

    int sparse[2 * N][21]; //! 2^X > 2 * N

    void dfs(int u, int p = -1) {
        pre[u] = TIME;
        nr[TIME] = u;

        sparse[id][0] = TIME++;
        fir[u] = id++;

        for(auto& v : graph[u]) if(v != p) {
            dfs(v, u);
            sparse[id++][0] = pre[u];
        }
    }

    void calc() {
        dfs(0);
        for(int j = 1; (1 << j) <= id; j++) {
            for(int i = 0; i + (1 << j) - 1 < id; i++) {
                sparse[i][j] = min(sparse[i][j - 1], sparse[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int minq(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return min(sparse[l][k], sparse[r - (1 << k) + 1][k]);
    }


    int query(int a, int b) {
        a = fir[a], b = fir[b];
        if(a > b) swap(a, b);
        return nr[minq(a, b)];
    }

    void addEdge(int a, int b) {
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
};