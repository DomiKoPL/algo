template <int N> struct NumberOfCycles {
    // number of simple cycles in O(2^n * n)
    vi graph[N];
    bitset<N> mat[N];
    ll dp[1 << N][N]; // dp[mask][i] - number of paths from lowest bit in mask to i

    NumberOfCycles() {
        FOR(i, 1 << N) FOR(j, N) {
            dp[i][j] = 0;
        }
    }

    void addEdge(int a, int b) {
        graph[a].PB(b);
        graph[b].PB(a);
        mat[a][b] = mat[b][a] = 1;
    }

    ll calc() {
        FOR(i, N) dp[1 << i][i] = 1;
        FOR(mask, 1, 1 << N) {
            if(__builtin_popcount(mask) > 1) {
                FOR(i, N) {
                    if((mask & (1 << i)) and i != __builtin_ctz(mask)) {
                        TRAV(v, graph[i]) {
                            if(mask & (1 << v)) {
                                dp[mask][i] += dp[mask ^ (1 << i)][v];
                            }
                        }
                    }
                }
            }
        }

        ll res = 0;

        FOR(mask, 1, 1 << N) {
            FOR(i, N) {
                if(__builtin_popcount(mask) >= 3 and (mask & (1 << i)) and mat[__builtin_ctz(mask)][i]) {
                    res += dp[mask][i];
                }
            }
        }

        return res / 2;
    }
};
