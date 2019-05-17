class Dsu {
	vector<int>g, s; //group, size

	Dsu(int n) {
		g.resize(n);
		for (int i = 0; i < n; ++i) {
			g[i] = i;
			s[i] = 1;
		}
	}

	int find(int a){
		if(g[a] == a)return a;
		return g[a] = find(g[a]);
	}

	bool union(int a,int b) {
		a = find(a), b = find(b);
		if(a == b) return false;
		if(s[a] > s[b]) swap(a,b);

		s[b] += s[a];
		g[a] = b;
		
		return true;
	}
};