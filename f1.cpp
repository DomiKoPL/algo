// KMP
template <typename T>
vector<int> kmp_table(int n, const T &s) {
	vector<int> p(n, 0);
	int k = 0;
	for (int i = 1; i < n; i++) {
		while (k > 0 && !(s[i] == s[k])) {
			k = p[k - 1];
		}
		if (s[i] == s[k]) {
			k++;
		}
		p[i] = k;
	}
	return p;
}
template <typename T>
vector<int> kmp_table(const T &s) {
	return kmp_table((int) s.size(), s);
}
template <typename T>
vector<int> kmp_search(int n, const T &s, int m, const T &w, const vector<int> &p) {
	assert(n >= 1 && (int) p.size() == n);
	vector<int> res;
	int k = 0;
	for (int i = 0; i < m; i++) {
		while (k > 0 && (k == n || !(w[i] == s[k]))) {
			k = p[k - 1];
		}
		if (w[i] == s[k]) {
			k++;
		}
		if (k == n) {
			res.push_back(i - n + 1);
		}
	}
	return res;
	// returns 0-indexed positions of occurrences of w in s
}
template <typename T>
vector<int> kmp_search(const T &s, const T &w, const vector<int> &p) {
	return kmp_search((int) s.size(), s, (int) w.size(), w, p);
}

// manacher

template <typename T>
vector<int> manacher(int n, const T &s) {
	if (n == 0) {
		return vector<int>();
	}
	vector<int> res(2 * n - 1, 0);
	int l = -1, r = -1;
	for (int z = 0; z < 2 * n - 1; z++) {
		int i = (z + 1) >> 1;
		int j = z >> 1;
		int p = (i >= r ? 0 : min(r - i, res[2 * (l + r) - z]));
		while (j + p + 1 < n && i - p - 1 >= 0) {
			if (!(s[j + p + 1] == s[i - p - 1])) {
				break;
			}
			p++;
		}
		if (j + p > r) {
			l = i - p;
			r = j + p;
		}
		res[z] = p;
	}
	return res;
	// res[2 * i] = odd radius in position i
	// res[2 * i + 1] = even radius between positions i and i + 1
	// s = "abaa" -> res = {0, 0, 1, 0, 0, 1, 0}
	// in other words, for every z from 0 to 2 * n - 2:
	// calculate i = (z + 1) >> 1 and j = z >> 1
	// now there is a palindrome from i - res[z] to j + res[z]
	// (watch out for i > j and res[z] = 0)
}
template <typename T>
vector<int> manacher(const T &s) {
  return manacher((int) s.size(), s);
}

// TRICKKK
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <class key, class cmp = less<key>>
using ordered_set = tree<key, null_type, cmp, rb_tree_tag,
 tree_order_statistics_node_update>;
template <class key, class cmp = less_equal<key>> 
using ordered_multiset = tree<key, null_type, cmp, rb_tree_tag,
 tree_order_statistics_node_update>;
//* find_by_order(k) - returns an iterator to the k-th largest element
//*     (counting from zero)
//* order_of_key(k)  - the number of items in a set that 
//*     are strictly smaller than k.
template <class key, class value, class cmp = less<key>>
using ordered_map = tree<key, value, cmp, rb_tree_tag, 
tree_order_statistics_node_update>;
using pref_trie = trie<string, null_type, trie_string_access_traits<>, 
pat_trie_tag, trie_prefix_search_node_update>;
// * prefix_range(s) - return iterator range, prefix equal to s

namespace debug {
template < typename _T >
inline void _debug(const char *s, _T x) {
    cerr << s << " = " << x << "\n";
}
template < typename _T, typename... args >
void _debug(const char *s, _T x, args... a) {
    while(*s != ',') cerr << *s++; cerr << " = " << x << ',';
    _debug(s + 1, a...); 
}

#if 1
#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
#define cerr cout
#else
#define debug(...) 69
#define cerr if(0) cout
#endif
}
using namespace debug;