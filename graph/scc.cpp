const int N = 1e5  + 7;
vi graf[N], comp[N], sccs;
int low[N], pre[N], snr[N];
bitset<N>vis, naS;
int TIME = 1;
stack<int>Q;

void DFS(int u) {
	vis[u] = naS[u] = true;
	low[u] = pre[u] = ++TIME;
	Q.push(u);

	TRAV(v, graf[u]) {
		if (!vis[v]) {
			DFS(v);
			setmin(low[u], low[v]);
		}
		else if (naS[v]) {
			setmin(low[u], low[v]);
		}
	}
    
	if (low[u] == pre[u]) {
		sccs.PB(u);
		int w;
		do {
			w = Q.top(); Q.pop();
			comp[u].PB(w);
			snr[w] = u;
			naS[w] = false;
		} while(w != u);
	}
}

vi stree[N];
void build(int n) {
	FOR(i, n) if(!vis[i]) {
		DFS(i);
	}

	bitset<N> temp;
	TRAV(u, sccs) {
		TRAV(i, comp[u]) TRAV(v, graf[i]) {
			if(snr[v] != u and !temp[snr[v]]) {
				stree[u].PB(snr[v]);
				temp[snr[v]] = 1;
			}
		}
		
		TRAV(v, graf[u]) temp[snr[v]] = 0;
	}
}