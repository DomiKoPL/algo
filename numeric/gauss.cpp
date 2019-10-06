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


ll inv(ll a, ll n = MOD - 2) {
	ll r = 1;
	while(n) {
		if(n & 1) r = (r * a) % MOD;
		a = (a * a) % MOD;
		n /= 2;
	}
	return r;
}

ll det(vvll gaus) {
	int n = SZ(gaus), m = SZ(gaus[0]);
	ll res = 1;
	FOR(i, 0, n) {
		if(gaus[i][i] == 0) {
			FOR(j, i + 1, n) {
				if(gaus[j][i] != 0) {
					FOR(x, 0, m) swap(gaus[i][x], gaus[j][x]);
					res = MOD - res;
					break;
				}
			}
		}
		FOR(j, i + 1, n) {
			ll a = (gaus[j][i] * inv(gaus[i][i])) % MOD;
			FOR(x, i, m) {
				gaus[j][x] -= (gaus[i][x] * a) % MOD;
				gaus[j][x] = (gaus[j][x] + MOD) % MOD;
			}
		}
	}
	FOR(i, 0, n) res = (res * gaus[i][i]) % MOD;
	res = (res + MOD) % MOD;
	return res;
}