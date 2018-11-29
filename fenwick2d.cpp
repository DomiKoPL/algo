template <typename T>
struct fenwick2d{
	vector<vector<T> > fen;
	int n,m;

	fenwick2d(int _n,int _m) : n(_n), m(_m){
		fen.resize(n);
		for (int i = 0; i < n; ++i){
			fen[i].resize(m);
		}
	}

	inline int lsb(int x){
		return x & -x;
	}

	inline void modify(int x, int y, T val){
		for(int i = x; i < n; i += lsb(i)){
			for(int j = y; j < m; j += lsb(j)){
				fen[i][j] ^= val; // main operation
			}
		}
	}

	inline T get(int x,int y){
		T res{};
		for(int i = x; i > 0; i -= lsb(i)){
			for(int j = y; j > 0; j -= lsb(j)){
				res ^= fen[i][j]; // main operation
			}
		}
		return res;
	}
};

struct node{
	int val = ...;//set to default

	void operator += (node & other){
		...// val += other.val;
	}
};