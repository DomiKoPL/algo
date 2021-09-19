template <typename T> struct HLD {
	static const int N = 1e5 + 7;
	static const int TS = 1 << 17;
    
    T tree[2 * TS];
    // implement tree

	vi graph[N];
	int par[N], dep[N], heavy[N], head[N], pos[N];
	int cur_pos = 0;

	int dfs(int u) {
		int roz = 1, maxc = 0;
		TRAV(v, graph[u]) {
			if(v == par[u]) {
				continue;
			}
			par[v] = u;
			dep[v] = dep[u] + 1;
			int croz = dfs(v);
			roz += croz;
			if(croz > maxc) {
				maxc = croz;
				heavy[u] = v;
			}
		}
		return roz;
	}

	void make_paths(int u, int h) {
		head[u] = h;
		pos[u] = cur_pos++;
		if(heavy[u] != -1) {
			make_paths(heavy[u], h);
		}

		TRAV(v, graph[u]) {
			if(v != par[u] and v != heavy[u]) {
				make_paths(v, v);
			}
		}
	}

	T query(int a, int b) {
		T res = 0; // change
		for(; head[a] != head[b]; b = par[head[b]]) {
			if(dep[head[a]] > dep[head[b]]) {
				swap(a, b);	
			}
			
			T temp = getSeq(pos[head[b]], pos[b]);
			res += temp; // change
		}

		if(dep[a] > dep[b]) {
			swap(a, b);	
		}

		// (pos[a] + 1, pos[b]) - without 
		T temp = getSeq(pos[a], pos[b]);
		res += temp; // change 

		return res;
	}

	void build(int n) {
		cur_pos = 0;
		FOR(i, n) {
			par[i] = heavy[i] = -1;
		}

		dep[0] = 0;
		dfs(0);
		make_paths(0, 0);

		FOR(i, 2 * TS) {
            // reset tree
		}
	}

	void addEdge(int a, int b) {
		graph[a].PB(b);
		graph[b].PB(a);
	}
};