#define NDEBUG
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <ctime>
#include <map>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#define long int64_t

typedef int vertex;
typedef int edge;

template <class Derived>
struct RBST_node
{
    typedef Derived *node_p;
    node_p par = nullptr;
    node_p lch = nullptr;
    node_p rch = nullptr;
    int num_ = 1;
    virtual ~RBST_node() {}
    void set_lch(node_p u) {
        lch = u;
        if (u) u->par = static_cast<node_p>(this);
        pull();
    }
    void set_rch(node_p u) {
        rch = u;
        if (u) u->par = static_cast<node_p>(this);
        pull();
    }
    void pull() {
        num_ = 1 + num(lch) + num(rch);
        pull_state();
    }
    virtual void pull_state() = 0;
    static int num(node_p u) {
        return u ? u->num_ : 0;
    }
    static node_p root(node_p u) {
        if (!u) return u;
        while (u->par) {
            u = u->par;
        }
        return u;
    }
    static node_p join(node_p u, node_p v) {
        if (!u) return v;
        if (!v) return u;
        static_assert(sizeof(long) >= 8, "");
        if (rand() * static_cast<long>(num(u) + num(v)) < static_cast<long>(num(u)) * RAND_MAX) {
            u->set_rch(join(u->rch, v));
            return u;
        } else {
            v->set_lch(join(u, v->lch));
            return v;
        }
    }
    static std::pair<node_p,node_p> split(node_p u, bool erase_u) {
        assert(u);
        node_p l = u->lch, r = erase_u ? u->rch : u;
        u->set_lch(nullptr);
        while (u->par) {
            if (u->par->lch == u) {
                u = u->par;
                u->set_lch(r);
                r = u;
            } else {
                u = u->par;
                u->set_rch(l);
                l = u;
            }
        }
        if (l) l->par = nullptr;
        if (r) r->par = nullptr;
        return {l, r};
    }
};
 
template <class Derived>
struct ET_node : public RBST_node<Derived>
{
    typedef Derived *node_p;
    vertex id;
    bool active;
    ET_node(vertex id, bool activate)
        : id(id)
        , active(activate)
    {}
    virtual void move_activity(node_p to) {
        std::swap(active, to->active);
    }
};

template <class Origin, class Node>
class ET_tree
{
    typedef Node *node_p;
    const Origin& origin;
    const int n;
    std::unordered_map<edge,std::pair<node_p,node_p> > nodes;
    std::vector<node_p> occur;
    std::vector<std::unordered_set<node_p> > occurs;
public:
    ET_tree(const Origin& origin, int n)
        : origin(origin)
        , n(n)
        , occur(n)
        , occurs(n)
    {}
    ~ET_tree() {
        for (const auto& p : nodes) {
            delete p.second.first;
            delete p.second.second;
        }
    }
private:
    static node_p reroot(node_p u) {
        assert(u);
        auto p = Node::split(u, false);
        return Node::join(p.second, p.first);
    }
    void renew_occur(vertex a) {
        if (occurs[a].empty()) {
            occur[a] = nullptr;
        } else {
            node_p u = *occurs[a].begin();
            occur[a]->move_activity(u);
            occur[a] = u;
            for (; u; u = u->par) {
                u->pull_state();
            }
        }
    }
public:
    node_p root(vertex a) const {
        return Node::root(occur[a]);
    }
    bool connected(vertex a, vertex b) const {
        return a == b or (root(a) and root(a) == root(b));
    }
    void update(vertex a) {
        node_p u = occur[a];
        if (!u) return;
        origin.template update_node<node_p>(u, a);
        for (; u; u = u->par) {
            u->pull_state();
        }
    }
    void insert(vertex a, vertex b, edge e) {
        node_p u = occur[a];
        node_p v = occur[b];
        node_p ab = new Node(a, !u);
        node_p ba = new Node(b, !v);
        if (!u) {
            origin.template init_node<node_p>(ab, a);
            occur[a] = ab;
        } else {
            u = reroot(u);
        }
        if (!v) {
            origin.template init_node<node_p>(ba, b);
            occur[b] = ba;
        } else {
            v = reroot(v);
        }
        Node::join(Node::join(u, ab), Node::join(v, ba));
        nodes[e] = {ab, ba};
        occurs[a].insert(ab);
        occurs[b].insert(ba);
    }
    void erase(vertex a, vertex b, edge e) {
        const node_p ab = nodes[e].first;
        const node_p ba = nodes[e].second;
        occurs[a].erase(ab);
        occurs[b].erase(ba);
        if (ab->active) renew_occur(a);
        if (ba->active) renew_occur(b);
        nodes.erase(e);
        auto p = Node::split(ab, true);
        auto prev_num = Node::num(p.second);
        auto q = Node::split(ba, true);
        if (p.second == ba or Node::num(p.second) != prev_num) {
            Node::join(p.first, q.second);
        } else {
            Node::join(q.first, p.second);
        }
        delete ab;
        delete ba;
    }
};

class HDT98_layer
{
    typedef HDT98_layer this_t;
    struct node;
    typedef node *node_p;
    struct node : public ET_node<node> {
        int size_;
        char here, below_;
        node(vertex id, bool activate)
            : ET_node(id, activate)
            , size_(activate)
        {}
        void move_activity(node_p to) {
            ET_node::move_activity(to);
            std::swap(here, to->here);
        }
        void pull_state() {
            size_ = active + size(lch) + size(rch);
            below_ = here | below(lch) | below(rch);
        }
    };
    static int size(node_p u) {
        return u ? u->size_ : 0;
    }
    static char below(node_p u) {
        return u ? u->below_ : 0;
    }
    const int n;
    ET_tree<this_t,node> ET;
    std::unordered_map<vertex,std::unordered_set<edge> > F;
    std::unordered_map<vertex,std::unordered_map<edge,vertex> > H;
public:
    HDT98_layer(int n)
        : n(n)
        , ET(*this, n)
    {}
private:
    char state(vertex a) const {
        return (F.count(a) and !F.at(a).empty()) | (H.count(a) and !H.at(a).empty()) << 1;
    }
    template <class T, typename std::enable_if<std::is_same<T,node_p>::value>::type* = nullptr>
    void init_node(node_p u, vertex a) const {
        u->here = u->below_ = state(a);
    }
    template <class T, typename std::enable_if<std::is_same<T,node_p>::value>::type* = nullptr>
    void update_node(node_p u, vertex a) const {
        u->here = state(a);
    }
    void report_tree_edges(vertex a, std::vector<edge>& ret) {
        ret.insert(ret.end(), F[a].begin(), F[a].end());
        F[a].clear();
    }
    void report_tree_edges(node_p u, std::vector<edge>& ret) {
        if (!(below(u) & 1)) return;
        if (u->here & 1) report_tree_edges(u->id, ret);
        report_tree_edges(u->lch, ret);
        report_tree_edges(u->rch, ret);
    }
    bool search_nontree_edges(vertex a, node_p v, edge& repl, std::vector<edge>& trail, int& pass) {
        assert(v);
        for (auto it = H[a].begin(); it != H[a].end(); ) {
            const edge e = it->first;
            const vertex b = it->second;
            if (ET.root(b) == v) {
                repl = e;
                return true;
            }
            if (pass > 0) {
                --pass;
                ++it;
            } else {
                trail.push_back(e);
                H[a].erase(it++);
                H[b].erase(e);
                ET.update(b);
            }
        }
        ET.update(a);
        return false;
    }
    bool search_nontree_edges(node_p u, node_p v, edge& repl, std::vector<edge>& trail, int& pass) {
        if (!(below(u) & 2)) return false;
        if (u->here & 2 and search_nontree_edges(u->id, v, repl, trail, pass)) {
            return true;
        }
        return search_nontree_edges(u->lch, v, repl, trail, pass)
            or search_nontree_edges(u->rch, v, repl, trail, pass);
    }
public:
    bool connected(vertex a, vertex b) const {
        return ET.connected(a, b);
    }
    void insert_tree_edge(vertex a, vertex b, edge e, bool on) {
        ET.insert(a, b, e);
        if (on) {
            F[a].insert(e);
            ET.update(a);
        }
    }
    void insert_nontree_edge(vertex a, vertex b, edge e) {
        H[a][e] = b;
        H[b][e] = a;
        ET.update(a);
        ET.update(b);
    }
    void erase_tree_edge(vertex a, vertex b, edge e) {
        ET.erase(a, b, e);
        F[a].erase(e);
        ET.update(a);
    }
    void erase_nontree_edge(vertex a, vertex b, edge e) {
        H[a].erase(e);
        H[b].erase(e);
        ET.update(a);
        ET.update(b);
    }
    bool replace(vertex a, vertex b, edge& repl, std::vector<edge>& promote, std::vector<edge>& trail, int pass) {
        node_p u = ET.root(a);
        node_p v = ET.root(b);
        if (size(u) > size(v)) {
            std::swap(a, b);
            std::swap(u, v);
        }
        if (!v) {
            return false;
        } else if (!u) {
            return search_nontree_edges(a, v, repl, trail, pass);
        } else {
            bool ret = search_nontree_edges(u, v, repl, trail, pass);
            if (pass == 0) report_tree_edges(u, promote);
            return ret;
        }
    }
    friend class ET_tree<this_t,node>;
};

int lg(unsigned n)
{
    int ret = 0;
    while (n >> ret > 1) ++ret;
    return ret;
}

class HDT98
{
    const int n, k;
    int edge_count = 0;
    std::map<std::pair<vertex,vertex>,edge> edge_id;
    std::unordered_map<edge,std::pair<vertex,vertex> > endpoints;
    std::unordered_set<edge> tree_edges;
    std::unordered_map<edge,int> level;
    std::vector<HDT98_layer> F;
public:
    HDT98(int n)
        : n(n)
        , k(lg(n))
    {
        F.reserve(k);
        for (int i = 0; i < k; ++i) {
            F.emplace_back(n);
        }
    }
private:
    void insert_tree_edge(edge e, int l) {
        const auto& p = endpoints[e];
        for (int i = l; i >= 0; --i) {
            F[i].insert_tree_edge(p.first, p.second, e, i == l);
        }
    }
    bool erase_tree_edge(vertex a, vertex b, edge e) {
        const int l = level[e];
        for (int i = 0; i <= l; ++i) {
            F[i].erase_tree_edge(a, b, e);
        }
        for (int i = l; i >= 0; --i) {
            edge repl = -1;
            static std::vector<edge> promote, trail;
            promote.clear();
            trail.clear();
            F[i].replace(a, b, repl, promote, trail, k);
            for (const edge& e : promote) {
                ++level[e];
                const auto& p = endpoints[e];
                F[i+1].insert_tree_edge(p.first, p.second, e, true);
            }
            for (const edge& e : trail) {
                ++level[e];
                const auto& p = endpoints[e];
                F[i+1].insert_nontree_edge(p.first, p.second, e);
            }
            if (repl >= 0) {
                const auto& p = endpoints[repl];
                F[i].erase_nontree_edge(p.first, p.second, repl);
                tree_edges.insert(repl);
                insert_tree_edge(repl, i);
                return false;
            }
        }
        return true;
    }
public:
    bool insert(vertex a, vertex b) {
        if (a > b) std::swap(a, b);
        if (edge_id.count({a, b})) return false;
        const edge e = edge_count++;
        edge_id[{a, b}] = e;
        endpoints[e] = {a, b};
        level[e] = 0;
        if (connected(a, b)) {
            F[0].insert_nontree_edge(a, b, e);
            return false;
        } else {
            tree_edges.insert(e);
            F[0].insert_tree_edge(a, b, e, true);
            return true;
        }
    }
    bool erase(vertex a, vertex b) {
        if (a > b) std::swap(a, b);
        if (!edge_id.count({a, b})) return false;
        const edge e = edge_id[{a, b}];
        const int l = level[e];
        edge_id.erase({a, b});
        endpoints.erase(e);
        bool ret = false;
        if (tree_edges.count(e)) {
            ret = erase_tree_edge(a, b, e);
            tree_edges.erase(e);
        } else {
            F[l].erase_nontree_edge(a, b, e);
        }
        level.erase(e);
        return ret;
    }
    bool connected(vertex a, vertex b) const {
        return F[0].connected(a, b);
    }
};

using namespace std;
#include <set>

int main() {
	int n, m; cin >> n >> m;
	HDT98 solver(n);
	int last = 0;
	set<pair<int,int>> ed;

	while(m--) {
		int t, x, y; cin >> t >> x >> y;
		x = (x + last - 1) % n;
		y = (y + last - 1) % n;
		if(x < y) swap(x, y);
		if(t == 2) {
			int r = solver.connected(x, y);
			cout << r;
			last = r;
		} else {
			if(ed.count({x, y})) {
				ed.erase({x, y});
				solver.erase(x, y);
			} else {
				ed.insert({x, y});
				solver.insert(x, y);
			}
		}
	}
}