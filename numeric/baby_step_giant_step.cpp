ll solve(ll a, ll b, ll m) {
    ll n = sqrt(m) + 1;
    ll an = 1;
    FOR(i, n) {
        an = (an * a) % m;
    }
    unordered_map<ll, ll> M;
    for(ll p = 1, cur = an; p <= n; p++) {
        if(!M.count(cur)) {
            M[cur] = p;
        }
        cur = (cur * an) % m;
    }

    ll res = LLINF;
    for(ll q = 0, cur = b; q <= n; q++) {
        if(M.count(cur)) {
            ll r = M[cur] * n - q;
            setmin(res, r);
        }
        cur = (cur * a) % m;
    }

    return (res < LLINF ? res : -1);
}