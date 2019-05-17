template <class T> struct Fenwick2D {
	vector<vector<T>> fen; // [0, ..., n - 1] [0, ..., m  - 1]
	int n, m;

	Fenwick2D(int n, int m) : n(n), m(m) { 
        fen.resize(n, vector<T>(m)); 
    }

	void upd(int x, int y, T val) { // [0, ..., x][0, ..., y] += val
        for(int i = x; i < n; i |= (i + 1)) {
            for(int j = y; j < n; j |= (j + 1)) {
                fen[i][j] += val;
            }
        }
	}

	T get(int x, int y) { // return sum of [0, ..., x][0, ..., y]
		T res{};
        for(int i = x; i >= 0; i = (i & (i + 1)) - 1) {
            for(int j = y; j >= 0; j = (j & (j + 1)) - 1) {
                res += fen[i][j];
            }
        }
		return res;
	}
};