template <typename T> T powmod(T a, T b, T mod) {
    T res = 1;
    while(b) {
        if(b &  1) {
            res = (1ll * res * a) % mod;
        }
        a = (1ll * a * a) % mod;
        b /= 2;
    }
    return res;
}

template <typename T> T generator(T mod) {
    vector<T> fact;
    T phi = mod - 1, n = phi;
    for(T i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            fact.PB(i);
            while(n % i == 0) {
                n /= i;
            }
        }
    }
    if(n > 1) {
        fact.PB(n);
    }

    for(T res = 2; res <= mod; res++) {
        bool good = true;
        TRAV(i, fact) {
            if(powmod(res, phi / i, mod) == 1) {
                good = false;
                break;  
            }
        }
        if(good) {
            return res;
        }
    }
    return -1;
}