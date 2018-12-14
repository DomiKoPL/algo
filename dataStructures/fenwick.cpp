template <typename T>
struct fenwick{
	vector<T> fen;
	int n;//size

	fenwick(int _n) : n(_n){
		fen.resize(n);
	}

	inline int lsb(int x){
		return x & -x;
	}

	inline void modify(int x, T val){
		for(int i = x; i < n; i += lsb(i)){
			fen[i] += val; // main operation
		}
	}

	inline T get(int x){
		T res{};
		for(int i = x; i > 0; i -= lsb(i)){
			res += fen[i]; // main operation
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