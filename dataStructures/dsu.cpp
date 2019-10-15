struct Dsu {
	vector<int>g, s; //group, size

	Dsu(int n) {
		g.resize(n);
		s.resize(n);
		for (int i = 0; i < n; ++i) {
			g[i] = i;
			s[i] = 1;
		}
	}

	int Find(int a){
		if(g[a] == a)return a;
		return g[a] = Find(g[a]);
	}

	bool Union(int a,int b) {
		a = Find(a), b = Find(b);
		if(a == b) return false;
		if(s[a] > s[b]) swap(a,b);

		s[b] += s[a];
		g[a] = b;
		
		return true;
	}
};