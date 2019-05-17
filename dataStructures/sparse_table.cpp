template <class T> struct SparseTable {
    vector<vector<T>> sparse;
    int n, m; // m >= ceil(flor(n))
    SparseTable() {}
    SparseTable(vector<T> a, int n, int m) : n(n), m(m) {
        for(int i = 0; i < n; i++) {
            sparse[i][0] = a[i];
        }
    }
    void make() {
        for(int j = 1; (1 << j) <= n; j++) {
            for(int i = 1; i + (1 << j) - 1 <= n; i++) {
                sparse[i][j] = gcd(sparse[i][j - 1], sparse[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T query(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return gcd(sparse[l][k], sparse[r - (1 << k) + 1][k]);
    }
};