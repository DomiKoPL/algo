
struct twoSat {
    int n;
    vector<vector<int>> graf, grafT; //k - 2 * k - on , 2 * k + 1 - zaprzeczenie
    vector<bool> used;
    vector<int> order, comp;
    vector<bool> assignment;

    twoSat(int n) : n(n) {
        graf.resize(n);
        grafT.resize(n);
        used.resize(n, false);
        comp.resize(n, -1);
        assignment.resize(n / 2);
    }   

    //* a v b = !a => b i !b => a
    void addEdge(int a, int b) {
        int x = abs(a) - 1, y = abs(b) - 1; // -a to zaprzeczenie a
        x *= 2;
        y *= 2;
        graf[x + (a > 0 ? 1 : 0)].push_back(y + (b > 0 ? 0 : 1));
        graf[y + (b > 0 ? 1 : 0)].push_back(x + (a > 0 ? 0 : 1));
    }

    //* a v a = !a => a
    void setTrue(int a) {
        a--; 
        graf[a * 2 + 1].push_back(a * 2);
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

    bool solve() {
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