template <class T> struct Fenwick {
	vector<T> fen; // [0, ..., n - 1]
	int n;

	Fenwick(int n) : n(n) { 
        fen.resize(n); 
    }

	void upd(int x, T val) { // [0, ..., x] += val
        for(; x < n; x |= (x + 1)) {
            fen[x] += val;
        }
	}

	T get(int x) { // return sum of [0, ..., x]
		T res{};
        for(; x >= 0; x = (x & (x + 1)) - 1) {
            res += fen[x];
        }
		return res;
	}

	T get(int x, int y) { // return sum of [x, ..., y]
		return get(y) - (x > 0 ? get(x - 1) : 0);
	}
};