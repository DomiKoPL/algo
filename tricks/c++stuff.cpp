#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <class key, class cmp = less<key>> using ordered_set = 
    tree<key, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;
template <class key, class cmp = less_equal<key>> using ordered_multiset =
     tree<key, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;
//* find_by_order(k) - returns an iterator to the k-th largest element (counting from zero)
//* order_of_key(k)  - the number of items in a set that are strictly smaller than k.
template <class key, class value, class cmp = less<key>> using ordered_map = 
    tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;
using pref_trie = 
    trie<string, null_type, trie_string_access_traits<>, pat_trie_tag, trie_prefix_search_node_update>;
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