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

	vvi cntc, cnts;
	int id[N];
	int disttoc[N][L];

	int dfs3(int u, int p, int d) {
		int x = d;
		TRAV(v, graph[u]) {
			if(v != p and !dead[v]) {
				x = max(x, dfs3(v, u, d + 1));
			}
		}
		return x;
	}

	void dfs2(int u, vi& cnt, int p, int d, int clvl) {
		cnt[d] += val[u];
		disttoc[u][clvl] = d;
		TRAV(v, graph[u]) {
			if(v != p and !dead[v]) {
				dfs2(v, cnt, u, d + 1, clvl);
			}
		}
	}

	int dfs(int start, int cur_lvl) {
		int size = get_roz(start, -1);
		int cen = dfs1(start, size, -1);

		dead[cen] = true;
		lvl[cen] = cur_lvl;

		cntc[cen] = vi(dfs3(cen, cen, 1));
		cntc[cen][0] = val[cen];
		disttoc[cen][cur_lvl] = 0;

		TRAV(v, graph[cen]) {
			if(!dead[v]) {
				int sub = dfs(v, cur_lvl + 1);
				par[sub] = cen;

				cnts[sub] = vi(dfs3(v, cen, 2));

				dfs2(v, cnts[sub], cen, 1, cur_lvl);

				FOR(i, 0, SZ(cnts[sub])) {
					cntc[cen][i] += cnts[sub][i];
				}

				FOR(i, 1, SZ(cnts[sub])) {
					cnts[sub][i] += cnts[sub][i - 1];
				}
			}
		}

		FOR(i, 1, SZ(cntc[cen])) {
			cntc[cen][i] += cntc[cen][i - 1];
		}

		dead[cen] = false;
		return cen;
	}

	void decomposition() {
		dfs(0, 0);
	}

	int get(vi& cnt, int roz, int d) {
		return cnt[min(d, roz - 1)];
	}

	int query(int u, int d) {
		int cen = u, ch = -1, res = 0;
		while(true) {
			int d2 = d - disttoc[u][lvl[cen]];

			if(d2 >= 0) {
				if(cen == u) {
					res += get(cntc[cen], SZ(cntc[cen]), d2);
				} else {
					res += get(cntc[cen], SZ(cntc[cen]), d2) - get(cnts[ch], SZ(cnts[ch]), d2);
				}
			}

			ch = cen;
			if(lvl[cen] == 0) {
				break;
			}
			cen = par[cen];
		}

		return res;
	}
} // namespace centroid