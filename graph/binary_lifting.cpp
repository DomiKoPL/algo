namespace binary_lifting {
	int par[N][L], gl[N];

	void dfs(int u, int p) {
		TRAV(v, graph[u]) {
			if(v != p) {
				gl[v] = gl[u] + 1;
				par[v][0] = u;
				dfs(v, u);
			}
		}
	}

	void calc(int n) {
		gl[0] = par[0][0] = 0;
		dfs(0, -1);

		FOR(j, 1, L) {
			FOR(i, 0, n) {
				par[i][j] = par[par[i][j - 1]][j - 1];
			}
		}
	}

	int lca(int u, int v) {
		if(gl[v] > gl[u]) swap(u, v);
		for(int l = L - 1; l >= 0; l--) {
			if(gl[u] - (1 << l) >= gl[v]) {
				u = par[u][l];
			}
		}

		if(u == v) return u;
		for(int l = L - 1; l >= 0; l--) {
			if(par[u][l] != par[v][l]) {
				u = par[u][l];
				v = par[v][l];
			}
		}
		return par[u][0];
	}

	int dist(int u, int v) {
		return gl[u] + gl[v] - 2 * gl[lca(u, v)];
	}

	int get_mid(int u, int v) {
		if(gl[v] > gl[u]) swap(u, v);
		int d = dist(u, v) / 2;
		int m = u;
		for(int l = L - 1; l >= 0; l--) {
			if(d & (1 << l)) {
				m = par[m][l];
			}
		}
		return m;
	}
} // namespace binary_lifting