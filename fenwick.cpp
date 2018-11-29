template <typename T>
struct fenwick{
	vector<T> fen;
	int n;//size

	fenwick(int _n) : n(_n){
		fen.resize(n);
	}

	void modify(int v, T val){
		while(v < n){
			fen[v] += val;
			v |= (v + 1);
		}
	}

	T get(int v){
		T res{};
		while(v >= 0){
			res += fen[v];
			v = (v & (v + 1)) - 1;
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