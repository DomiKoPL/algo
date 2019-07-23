
const int N = 41;
int kr[N], kr2[N];
int sos[1 << 22];
vi graf[N];
map<int,int> pri[N];

void solve() {
    int n; re(n);
    vi a(n); re(a);
    if(n == 1) {
        prln(2);
        return;
    }

    FOR(i, 0, n) {
        graf[i].clear();
        pri[i].clear();
        int temp = a[i], k = 2;
        while(k * k <= temp) {
            while(temp % k == 0) {
                temp /= k;
                pri[i][k]++;
            }
            k++;
        }
        if(temp > 1) {
            pri[i][temp]++;
        }
    }

    FOR(i, 0, n) FOR(j, i + 1, n) {
        bool good = true;
        TRAV(x, pri[i]) {
            good &= x.second + pri[j][x.first] < 3;
        }
        TRAV(x, pri[j]) {
            good &= x.second + pri[i][x.first] < 3;
        }
        if(good) {
            graf[i].PB(j);
            graf[j].PB(i);
        }
    }

    int m = n >> 1;
    FOR(i, 0, m) {
        kr[i] = 1 << i;
        TRAV(j, graf[i]) {
            if(j < m) {
                kr[i] |= 1 << j;
            }
        }
    }

    FOR(i, 0, 1 << m) {
        sos[i] = 0;
        int mask = (1 << m) - 1;
        FOR(j, 0, m) {
            if((1 << j) & i) {
                mask &= kr[j];
            }
        }
        if((mask & i) == i) {
            sos[i] = 1;
        }
    }

    FOR(bit, 0, m) {
        FOR(mask, 0, 1 << m) {
            if(mask & (1 << bit)) {
                sos[mask] += sos[mask ^ (1 << bit)];
            }
        }
    }

    FOR(i, 0, n - m) {
        kr[i] = 1 << i;
        TRAV(j, graf[i + m]) {
            if(j >= m) {
                kr[i] |= 1 << (j - m);
            }
        }
    }

    FOR(i, 0, m) {
        kr2[i] = 0;
        TRAV(j, graf[i]) {
            if(j >= m) {
                kr2[i] |= 1 << (j - m);
            }
        }
    }

    ll res = 0;
    FOR(i, 0, 1 << (n - m)) {
        bool good = true;
        FOR(j, 0, n - m) {
            if((i >> j) & 1) {
                good &= (kr[j] & i) == i;
            }
        }
        if(good) {
            int sub = 0;
            FOR(j, 0, m) {
                if((kr2[j] & i) == i) {
                    sub |= 1 << j;
                }
            }
            res += sos[sub];
        }
    }
    prln(res);
}