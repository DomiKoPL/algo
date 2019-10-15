int Id(int a) { return 2 * a; }
int Not(int a) { return a ^ 1; }

template <int N> struct TwoSat {
    vector<int> graf[2 * N], grafT[2 * N]; //k - 2 * k - on , 2 * k + 1 - zaprzeczenie
    bitset<2 * N> used;
    bitset<N> assignment;
    vector<int> order;
    int comp[2 * N];

    TwoSat() {
        fill(comp, comp + 2 * N, -1);
    }

    //* a v b = !a => b i !b => a
    void addOr(int a, int b) {
        graf[Not(a)].push_back(b);
        graf[Not(b)].push_back(a);
    }

    //* a v a = !a => a
    void setTrue(int a) {
        graf[Not(a)].push_back(a);
    }

    void dfs1(int v) {
        used[v] = true; 
        for (int u : graf[v]) {
            if (!used[u])
                dfs1(u);
        }
        order.push_back(v);
    }

    void dfs2(int v, int cl) {
        comp[v] = cl;
        for (int u : grafT[v]) {
            if (comp[u] == -1)
                dfs2(u, cl);
        }
    }

    bool solve(int n) {
        n = n * 2;

        for (int i = 0; i < n; i++) {
            for (auto& v : graf[i]) {
                grafT[v].push_back(i);
            }
        }

        for (int i = 0; i < n; i++) {
            if (!used[i]) {
                dfs1(i);
            }
        }

        int id = 0;
        for (int i = 0; i < n; i++) {
            int v = order[n - i - 1];
            if (comp[v] == -1) {
                dfs2(v, id++);
            }
        }

        for (int i = 0; i < n; i += 2) {
            if (comp[i] == comp[i + 1])
                return false;
            assignment[i / 2] = comp[i] > comp[i + 1];
        }

        return true;
    }
};