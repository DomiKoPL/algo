namespace centroid {
	bitset<N> dead, val;
	int roz[N];
	int lvl[N], par[N];

	int get_roz(int u, int p) {
		roz[u] = 1;
		TRAV(v, graph[u]) {
			if(v != p and !dead[v]) {
				roz[u] += get_roz(v, u);
			}
		}
		return roz[u];
	}
	
	int dfs1(int u, int size, int p) {
		TRAV(v, graph[u]) {
			if(v != p and !dead[v]) {
				if(roz[v] > size / 2) {
					return dfs1(v, size, u);
				}
			}
		}
		return u;
	}

	int dfs(int start, int cur_lvl) {
		int size = get_roz(start, -1);
		int cen = dfs1(start, size, -1);

		dead[cen] = true;
		lvl[cen] = cur_lvl;

		TRAV(v, graph[cen]) {
			if(!dead[v]) {
				int sub = dfs(v, cur_lvl + 1);
				par[sub] = cen;

			}
		}

		dead[cen] = false;
		return cen;
	}

	void decomposition() {
		dfs(0, 0);
	}
} // namespace centroid