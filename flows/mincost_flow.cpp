
template<int N> struct mcf { // assume no negative cycles
    #define f first
    #define s second
    struct Edge { int v, rev; ll flow, cap, cost; };

    vector<Edge> adj[N];
 
    void addEdge(int u, int v, ll cap, ll cost) {
        debug(u, v, cap, cost);
        Edge a{v, SZ(adj[v]), 0, cap, cost}, b{u, SZ(adj[u]), 0, 0, -cost};
        adj[u].PB(a), adj[v].PB(b);
    }
 
    int ST, EN;
    pii pre[N]; // previous vertex, edge label on path
    pll cost[N]; // tot cost of path, amount of flow
    ll totFlow, totCost, curCost;
 
    void reweight() { // ensures all non-negative edge weights
    	for(int i = 0; i < N; i++) TRAV(p,adj[i]) p.cost += cost[i].f - cost[p.v].f;
    }
 
    bool spfa() { // reweighting will ensure that there will be negative weights only during the first time you run this
        for(int i = 0; i < N; i++) cost[i] = {INF, 0};
        cost[ST] = {0,INF};

        using pli = pair<ll, int>;
        priority_queue<pli, vector<pli>, greater<pli>> todo;
        todo.push({0, ST});
 
        while (SZ(todo)) {
            auto x = todo.top(); todo.pop();
            if (x.f > cost[x.s].f) continue;
            
            TRAV(a,adj[x.s]) {
                if (x.f + a.cost < cost[a.v].f and a.flow < a.cap) {
                    pre[a.v] = {x.s, a.rev};
                    cost[a.v] = {x.f + a.cost, min(a.cap - a.flow, cost[x.s].s)};
                    todo.push({cost[a.v].f, a.v});
                }
            }
        }
 
        curCost += cost[EN].f;
        return cost[EN].s;
    }
 
    void backtrack() {
        auto f = cost[EN].s; totFlow += f, totCost += curCost*f;
        for (int x = EN; x != ST; x = pre[x].f) {
            adj[x][pre[x].s].flow -= f;
            adj[pre[x].f][adj[x][pre[x].s].rev].flow += f;
        }
    }
 
    pll minCostFlow(int _ST, int _EN) {
        ST = _ST, EN = _EN; 
        totFlow = totCost = curCost = 0;
        spfa();
        while (1) {
            reweight();
            if (!spfa()) return {totFlow, totCost};
            backtrack();
        }
    }
};