
using typ = __int128;

typ fast(typ a, typ b, typ mod){
	typ ret = 1;
    for(; b; b /= 2) {
        if(b & 1) ret = (ret * a) % MOD;
        a = (a * a) % MOD;
    }
	return ret;
}

typ get(typ p){
	typ t = 2;
	while(fast(t, (p - 1) / 2, p) == 1)
		++t;
	return t;
}

// Jeśli -1 to nie ma rozwiązania,
// wpp. rozwiązanie to r i -r, p jest pierwsze
typ dsr(typ v, typ p) {	
	if(v == 0)
		return 0;

	if(p == 2)
		return 1;
	
	if(fast(v, (p - 1) / 2, p) == p - 1)
		return -1;
	
	typ q = p - 1, s = 0;
	while(!(q & 1))
		q /= 2, ++s;
	
	if(s == 1)
		return fast(v, (p + 1) / 4, p);
	
	typ z = get(p);
	typ c = fast(z, q, p);
	typ r = fast(v, (q + 1) / 2, p);
	typ t = fast(v, q, p);
	typ m = s;
	
	while(t != 1){
		typ tt = t;
		typ i = 0;
		
		while(tt != 1){
			tt = (1LL * tt * tt) % p;
			++i;
		}
		
		typ b = fast(c, fast(2, m - i - 1, p - 1), p);
		typ b2 = (1LL * b * b) % p;
		
		r = (1LL * r * b) % p;
		t = (1LL * t * b2) % p;
		c = b2;
		m = i;
	}
	
	return r;
}