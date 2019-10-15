using ull = unsigned long long;
#define FOR(a, b, c) for(int a = (b); a < (c); a++)
#define SZ(a) (int)((a).size())

// nim-multiplication
// https://en.wikipedia.org/wiki/Nimber#Multiplication
// https://petr-mitrichev.blogspot.com/2019/01/a-galois-week.html

const int N = 64;

// if it is Fermat-2-power
bitset<N> fpot2;

// result for nim-multiplication of powers of 2
ull nimmul[N][N]; 

ull precalc(vector<int> pot) {
    ull res = 1;
    FOR(i, 1, SZ(pot)) {
        if(pot[i - 1] == pot[i]) {
            vector<int> pot1, pot2;
            FOR(j, 0, i - 1) {
                pot1.push_back(pot[j]);
                pot2.push_back(pot[j]);
            }

            FOR(j, i, SZ(pot)) {
                pot1.push_back(pot[j]);
            }
            FOR(j, 0, pot[i]) {
                pot2.push_back(j);
            }
            FOR(j, i + 1, SZ(pot)) {
                pot2.push_back(pot[j]);
            }
            sort(pot2.begin(), pot2.end());

            return precalc(pot1) ^ precalc(pot2);
        }
    }

    for(auto& i : pot) {
        res = res << (1 << i);
    }

    return res;
}

void pre() {
    // find all Fermat-2-powers
    for(int i = 1; i < N; i *= 2) {
        fpot2[i] = true;
    }
    
    FOR(i, 0, N) {
        FOR(j, i, N) {
            if(i == 0) {
                nimmul[i][j] = 1ull << j;
            } else if(fpot2[i] and fpot2[j]) {
                if(i == j) {
                    nimmul[i][j] = 3 * (1ull << (j - 1));
                } else {
                    nimmul[i][j] = (1ull << (i + j));
                }
            } else {
                vector<int> pot;
                FOR(k, 0, 6) {
                    if((1 << k) & i) pot.push_back(k);
                    if((1 << k) & j) pot.push_back(k);
                }
                nimmul[i][j] = precalc(pot);
            }
        }
    }

    FOR(i, 0, N) {
        FOR(j, 0, i) {
            nimmul[i][j] = nimmul[j][i];
        }
    }
}


ull nimMult(ull a, ull b) {
    ull res = 0;
    FOR(i, 0, N) {
        if(a & (1ull << i)) {
            FOR(j, 0, N) {
                if(b & (1ull << j)) {
                    res ^= nimmul[i][j];
                }
            }
        }
    }
    return res;
}

ull nimInv(ull a) {
    ull k = -2, res = 1;
    for(; k; k >>= 1) {
        if(k & 1) res = nimMult(res, a);
        a = nimMult(a, a);
    }
    return res;
}