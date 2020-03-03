struct hash_struct {
    const ll MOD = 1e9 + 2089;
    const ll P = 13;
    vector<ll> pot, hasz;

    hash_struct(string const& s) {
        int n = s.size();
        pot.resize(n + 1);
        hasz.resize(n);
        
        pot[0] = 1;
	    FOR(i, 1, n + 1) pot[i] = (pot[i - 1] * P) % MOD;

        hasz[0] = (s[0] - '0' + 1);
        FOR(i, 1, n) {
            hasz[i] = (hasz[i - 1] * P + (s[i] - '0' + 1)) % MOD;	
        }
    }

    ll get(int a, int b) { // a - 0 indexed begin, b - length
        if(a == 0) return hasz[a + b - 1];
        return (hasz[a + b - 1] + MOD - (hasz[a - 1] * pot[b] % MOD)) % MOD;
    }
};