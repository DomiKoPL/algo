// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse4")

#include <bits/stdc++.h>

using namespace std;

#define GET_MACRO(_1, _2, _3, _4, NAME, ...) NAME
#define __FOR3(i, a, n, inc) for(int i = (a); (inc) > 0 ? i < (n) : i >= (n); i += (inc))
#define __FOR2(i, a, n) __FOR3(i, a, n, 1)
#define __FOR1(i, n) __FOR2(i, 0, n)
#define __FOR0(n) __FOR1(_, n)
#define FOR(...) GET_MACRO(__VA_ARGS__, __FOR3, __FOR2, __FOR1, __FOR0)(__VA_ARGS__)

#define BOOST 			ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ELO             exit(0)
#define ALL(a) 			(a).begin(), (a).end()
#define SZ(a) 			(int)(a).size()
#define TRAV(a, b) 		for (auto& a : b)
#define REV(a)          reverse(ALL(a))
#define SORT(a)         sort(ALL(a))
#define SORTR(a)        SORT(a), REV(a)
#define PB              push_back
#define F               first
#define S               second
using ll = 				long long;
using ld = 				long double; // 'long double' is 2.2 times slower than double
using pii = 			pair<int, int>;
using pll = 			pair<ll, ll>;
using pld =             pair<ld, ld>;
using vb =				vector<bool>;
using vi = 				vector<int>;
using vvi =             vector<vi>;
using vll = 			vector<ll>;
using vvll =            vector<vll>;
using vpii = 			vector<pii>;
using vpll = 			vector<pll>;
using vld =             vector<ld>;
using vpld =            vector<pld>;

constexpr int MOD = 1e9 + 7; // 998244353
constexpr int INF = MOD;
constexpr ll LLINF = 1e18;
const ld PI = acos(-1);

template <class T> inline bool setmin(T& a, T b) {if (a > b) return a = b, 1; return 0; }
template <class T> inline bool setmax(T& a, T b) {if (a < b) return a = b, 1; return 0; }

namespace input {
    template <class T> istream &operator>>(istream &os, vector<T> & vec) { for (auto& u : vec) os >> u; return os; }
    template<class T1, class T2> istream& operator>>(istream& os, pair<T1, T2>& p) { return os >> p.first >> p.second; }
    template <class T, size_t N> istream& operator>>(istream& os, array<T, N>& a) { for (auto& u : a) os >> u; return os; }

    void re() {}
    template <typename T, typename... args> void re(T& x, args&... tail) { cin >> x; re(tail...); }
} // namespace input
using namespace input;

namespace output {
    template <class T> ostream &operator<<(ostream &os, const vector<T> & vec){for (const auto& u : vec) os << u << " "; return os; }
    template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1, T2>& p) { return os << p.first << " " << p.second; }
    template <class T> ostream &operator<<(ostream &os, set<T> & con) { for (const auto& u : con) os << u << " "; return os; }
    template <class T, size_t N> ostream& operator<<(ostream& os, array<T, N>& a) { for (const auto& u : a) os << u << " "; return os; }
    
    void pr() {}
    template <typename T> void pr(const T& x) { cout << x; }
    template <typename T, typename... args> void pr(const T& x, const args&... tail) { cout << x << " "; pr(tail...);}
    template <typename T> void prs(const T& x) { cout << x << " "; }
    template <typename T, typename... args> void prs(const T& x, const args&... tail) { cout << x << " "; prs(tail...);}
    template <typename... args> void prln(const args&... tail) { pr(tail...); cout << "\n";}
} // namespace output 
using namespace output;

namespace pair_magic {
	#define PT1T2 pair<T1,T2>
	#define TT1T2 template<class T1, class T2>
	TT1T2 inline PT1T2 operator+(const PT1T2 &p1, const PT1T2 &p2) { return PT1T2(p1.first + p2.first, p1.second + p2.second); }
	TT1T2 inline PT1T2& operator+=(PT1T2 &p1, const PT1T2 &p2) { p1.first += p2.first, p1.second += p2.second; return p1; }
	TT1T2 inline PT1T2 operator-(const PT1T2 &p1, const PT1T2 &p2) { return PT1T2(p1.first - p2.first, p1.second - p2.second); }
	TT1T2 inline PT1T2& operator-=(PT1T2 &p1, const PT1T2 &p2) { p1.first -= p2.first, p1.second -= p2.second; return p1; }
	#undef PT1T2
	#undef TT1T2
}
using namespace pair_magic;

namespace random_nsp {
	thread_local std::mt19937 gen{std::random_device{}()};
	template <typename T>T random(T min, T max){using dist = std::conditional_t<std::is_integral<T>::value, std::uniform_int_distribution<T>, std::uniform_real_distribution<T>>;return dist{min, max}(gen);}
	template <typename T> T randomINT(T min, T max) { return std::uniform_int_distribution<T>{min, max}(gen); }
}
using namespace random_nsp;

namespace triple {
	#define TT1T2T3 template<class T1, class T2, class T3>
	#define TRT1T2T3  triple<T1, T2, T3>
	TT1T2T3 struct triple { T1 a; T2 b; T3 c; triple() : a(T1()), b(T2()), c(T3()) {}; triple(T1 _a, T2 _b, T3 _c) :a(_a), b(_b), c(_c) {} };
	TT1T2T3 bool operator<(const TRT1T2T3&t1, const TRT1T2T3&t2) { if (t1.a != t2.a)return t1.a < t2.a; else if (t1.b != t2.b)return t1.b < t2.b; else return t1.c < t2.c; }
	TT1T2T3 bool operator>(const TRT1T2T3&t1, const TRT1T2T3&t2) { if (t1.a != t2.a)return t1.a > t2.a; else if (t1.b != t2.b)return t1.b > t2.b; else return t1.c > t2.c; }
	TT1T2T3 bool operator==(const TRT1T2T3&t1, const TRT1T2T3&t2) { return (t1.a == t2.a && t1.b == t2.b && t1.c == t2.c); }
	TT1T2T3 inline istream& operator >> (istream& os, triple<T1, T2, T3>& t) { return os >> t.a >> t.b >> t.c; }
	TT1T2T3 ostream& operator << (ostream& os, const triple<T1, T2, T3>& t) { return os << t.a << " " << t.b << " " << t.c; }
	#undef TRT1T2T3
	#undef TT1T2T3
	using tri =  triple<int, int, int>;
	using trll = triple<ll, ll, ll>;
	using vtri = vector<tri>;
    using vtrll = vector<trll>;
}
using namespace triple;

template <class T> T invGeneral(T a, T b) { // 0 < a < b, gcd(a,b) = 1
    a %= b;
    if (a == 0) return b == 1 ? 0 : -1;
    T x = invGeneral(b, a); 
    return x == -1 ? -1 : ((1-(ll)b * x) / a + b) % b;
}

template<class T, int MOD> struct modular {
	T val; 
	explicit operator T() const { return val; }
	modular() { val = 0; }
	modular(const ll& v) { 
		val = (-MOD <= v && v <= MOD) ? v : v % MOD;
		if (val < 0) val += MOD;
	}
	friend ostream& operator<<(ostream& os, const modular& a) { return os << a.val; }
	friend void pr(const modular& a) { pr(a.val); }
	friend void re(modular& a) { ll x; re(x); a = modular(x); }

	friend bool operator==(const modular& a, const modular& b) { return a.val == b.val; }
	friend bool operator!=(const modular& a, const modular& b) { return !(a == b); }
	friend bool operator<(const modular& a, const modular& b) { return a.val < b.val; }

	modular operator-() const { return modular(-val); }
	modular& operator+=(const modular& m) { if ((val += m.val) >= MOD) val -= MOD; return *this; }
	modular& operator-=(const modular& m) { if ((val -= m.val) < 0) val += MOD; return *this; }
	modular& operator*=(const modular& m) { val = (ll)val*m.val%MOD; return *this; }
	friend modular pow(modular a, ll p) {
		modular ans = 1; for (; p; p /= 2, a *= a) if (p&1) ans *= a;
		return ans;
	}
	friend modular inv(const modular& a) { 
		auto i = invGeneral(a.val,MOD); assert(i != -1);
		return i;
	} // equivalent to return exp(b,MOD-2) if MOD is prime
	modular& operator/=(const modular& m) { return (*this) *= inv(m); }
	
	friend modular operator+(modular a, const modular& b) { return a += b; }
	friend modular operator-(modular a, const modular& b) { return a -= b; }
	friend modular operator*(modular a, const modular& b) { return a *= b; }
	friend modular operator/(modular a, const modular& b) { return a /= b; }
};

using mi = modular<int, MOD>;
using pmi = pair<mi,mi>;
using vmi = vector<mi>; 
using vpmi = vector<pmi>;

namespace debug {
    template < typename _T > inline void _debug(const char *s, _T x) { cerr << s << " = " << x << "\n"; }
    template < typename _T, typename... args > void _debug(const char *s, _T x, args... a) { while(*s != ',') cerr << *s++; cerr << " = " << x << ','; _debug(s + 1, a...); }
    
    #if defined(LOCAL) && 1
        #define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
        #define cerr cout
    #else
        #define debug(...) 1999
        #define cerr if(0) cout
    #endif
} // namespace debug
using namespace debug;

///____________CODE____________///

int main() {
    BOOST;
    
}