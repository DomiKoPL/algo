struct Dsu {
	vector<int> gr, roz;

	Dsu(int n) {
		gr.resize(n);
		iota(begin(gr), end(gr), 0);
		roz.resize(n, 1);
	}

	int Find(int a){
		return (gr[a] == a ? a : gr[a] = Find(gr[a]));
	}

	bool Union(int a, int b) {
		a = Find(a), b = Find(b);
		if(a == b) return false;
		if(roz[a] > roz[b]) swap(a,b);

		roz[b] += roz[a];
		return gr[a] = b, true;
	}
};