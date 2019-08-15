template <class T>
void gaussianElimination(vector<vector<T>> tab, int n, int m) {
	FOR(i, 0, n) {
		FOR(j, i + 1, n) {
			ll a = (1ll * gaus[j][i] * inverse(gaus[i][i])) % MOD;
			FOR(x, i, m) {
				gaus[j][x] -= (1ll * gaus[i][x] * a) % MOD;
				gaus[j][x] = (gaus[j][x] + MOD) % MOD;
			}
		}
	}
 
	vector<T> c(m - 1);
	for(int i = m - 1; i >= 0; i--) {
		FOR(j, i + 1, m) {
			gaus[i][m] = (1ll * gaus[i][m] + MOD - ((1ll * gaus[i][j] * c[j]) % MOD)) % MOD;
		}
		c[i] = (1ll * gaus[i][m] * inverse(gaus[i][i])) % MOD;
		c[i] = (c[i] + MOD) % MOD;
	}
}