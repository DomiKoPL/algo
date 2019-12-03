int n, k;
int n, k;
ll pref[N];
struct { int l, p, id; } Q[N];

ll f(int i, int j) {
    ll res = pref[i] + pref[j];
    res -= pref[(i + j) / 2] + pref[(i + j + 1) / 2];
    return res;
}

ll dp[N];
int dl[N];

bool better(int i, int j, int k) {
    ll a = dp[i] + f(i, k);
    ll b = dp[j] + f(j, k);
    if(a != b) {
        return a < b;
    }
    return dl[i] < dl[j];
}


// izi trick for dp with quadrangle inequality
// Dp[x] = min{dp[i] + f(i, x)}
// where i <= j, then f(i, j) + f(i + 1, j + 1) <=
//                      f(i + 1, j) + f(i, j + 1)
bool good(ll pen) {
    Q[1] = {0, n, 0};
    int pocz = 1, kon = 1;
    FOR(i, 1, n + 1) {
        while(pocz <= kon and Q[pocz].p < i) {
            pocz++;
        }

        dl[i] = dl[Q[pocz].id] + 1;
        dp[i] = dp[Q[pocz].id] + f(Q[pocz].id, i) + pen;
        
        if(kon < pocz or better(i, Q[kon].id, n)) {
            while(pocz <= kon and better(i, Q[kon].id, Q[kon].l)) {
                kon--;
            }
            
            if(kon < pocz) {
                Q[++kon] = {i, n, i};
            } else {
                auto znajdz = [&](auto& q, auto i) {
                    auto[l, p, id] = q;

                    while(l <= p) {
                        int mid = l + p >> 1;
                        if(better(i, id, mid)) {
                            p = mid - 1;
                        } else {
                            l = mid + 1;
                        }
                    }
                    return p + 1;
                };

                int podzial = znajdz(Q[kon], i);

                Q[kon].p = podzial - 1;
                Q[++kon] = {podzial, n, i};
            }
        }
    }

    return dl[n] <= k;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> k;
    FOR(i, 1, n + 1) {
        cin >> pref[i];
        pref[i] += pref[i - 1];
    }

    ll l = 0, p = pref[n], res = 0;

	// Alien's trick
    while(l <= p) {
        ll pen = l + p >> 1;
        if(good(pen)) {
            res = dp[n] - pen * k;
            p = pen - 1;
        } else {
            l = pen + 1;
        }
    }

    cout << res << "\n";
}