struct DCP {
	struct DSU_save {
		int v, rankv, u, ranku;
		DSU_save() {}
		DSU_save(int v, int rv, int u, int ru) 
			: v(v), rankv(rv), u(u), ranku(ru) {}
	};
 
	vi p, rank;
	int comps; // components
	stack<DSU_save> op;
 
	DCP() {}
	DCP(int n) {
		p.resize(n);
		rank.resize(n);
		iota(ALL(p), 0);
		comps = n;
	}
	
	int Find(int u) {
		return (u == p[u] ? u : Find(p[u]));
	}
 
	bool Union(int u, int v) {
		u = Find(u), v = Find(v);
		if(u == v) {
			return false;
		}
		comps--;
		if(rank[u] > rank[v]) {
			swap(u, v);
		}
		op.push({u, rank[u], v, rank[v]});
		p[u] = v;
		if(rank[u] == rank[v]) {
			rank[v]++;
		}
		return true;
	}
 
	void rollback() {
		if(!SZ(op)) {
			return;
		}
		auto x = op.top(); op.pop();
		comps++;
		p[x.u] = x.u;
		rank[x.u] = x.ranku;
		p[x.v] = x.v;
		rank[x.v] = x.rankv;
	}
};
int n;
struct DCP_tree {
	struct query {
		int u, v;
		bool united;
		query(int u, int v) : u(u), v(v) {}
	};
 
	DCP dsu;
	vector<vector<query>> tree;
	int T;
 
	DCP_tree() {}
	DCP_tree(int T, int n) : T(T) {
		dsu = DCP(n);
		tree.resize(4 * T + 4);
	}
 
	void add(int v, int l, int r, int lo, int hi, query& q) {
		if(lo > hi) return;
		if(l == lo and r == hi) {
			tree[v].PB(q);
			return;
		}
		int mid = l + r >> 1;
		add(2 * v, l, mid, lo, min(hi, mid), q);
		add(2 * v + 1, mid + 1, r, max(lo, mid + 1), hi, q);
	}
	
	void add(query q, int l, int r) {
		add(1, 0, T - 1, l, r, q);
	}
 
	void dfs(int u, int l, int r, vi& res) {
		TRAV(q, tree[u]) {
			q.united = dsu.Union(q.u, q.v);
		}
 
		if(l == r) {
			res[l] = dsu.comps;
		} else  {
			int mid = l + r >> 1;
			dfs(2 * u, l, mid, res);
			dfs(2 * u + 1, mid + 1, r, res);
		}
 
		TRAV(q, tree[u]) {
			if(q.united) {
				dsu.rollback();
			}
		}
	}
 
	vi solve() {
		vi res(T);
		dfs(1, 0, T - 1, res);
		return res;
	}
};