namespace CRT {
    struct EGCD { ll x, y, d; };
    EGCD exGCD(ll a, ll b) {
        if(b == 0) return {1, 0, a};
        auto r = exGCD(b, a % b);
        return {r.y, r.x - a / b * r.y, r.d};
    }

	void norm(ll& x, ll mod) { 
		x %= mod;
		if(x < 0) x += mod;
	}
	ll lcm(ll a, ll b) {
		return a / gcd(a, b) * b;
	}

	pll solve(ll a1, ll n1, ll a2, ll n2) {
		auto[x1, y1, d] = exGCD(n1, n2);
		if((a2 - a1) % d != 0) {
			return {-1, -1}; // no solution
		}
		ll a3 = a1 + x1 * (a2 - a1) / d % (n2 / d) * n1;
		norm(a3, n1 * n2 / d);
		ll n3 = lcm(n1, n2);
		return {a3, n3};
	}

    // x = ai % ni
    // non-relatively prime modulo
    // {-1, -1} when no solution
	pll solve(vll a, vll n) {
		assert(SZ(a) == SZ(n));
		pll res = {a[0], n[0]};
		FOR(i, 1, SZ(a)) {
			res = solve(res.F, res.S, a[i], n[i]);
			if(res.F == -1) {
				return res;
			}
		}
		return res;
	}
}