template <int N> struct MobiusInversion {
    int prime[N + 1], cnt;
    bitset<N + 1> vis;
    int miu[N + 1];

    MobiusInversion() {
        miu[0] = miu[1] = 1;
        cnt = 0;

        FOR(i, 2, N + 1) {
            if(!vis[i]) {
                prime[cnt++] = i;
                miu[i] = -1;
            }

            FOR(j, 0, cnt) {
                int temp = i * prime[j];
                if(temp > N) break;

                vis[temp] = 1;
                
                if(i % prime[j] == 0) {
                    miu[temp] = 0;
                    break;
                }
                miu[temp] = -miu[i];
            }
        }

        FOR(i, 1, N + 1) {
            miu[i] += miu[i - 1];
        }
    }
};

const int N = 1e7;
MobiusInversion<N> mo;

ll f(ll n, ll m) {
    ll maxx = min(n, m);
    ll sum = 0;
    for(ll l = 1, r; l <= maxx; l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        sum += (mo.miu[r] - mo.miu[l - 1]) * (n / l) * (m / l);
    }
    return sum - 1;
}
