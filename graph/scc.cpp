vector <int> graf[MAXN];
int low[MAXN], preorder[MAXN];
bitset<MAXN>vis, naStacku;
int czas = 1;
stack<int>Q;
void DFS(int u) {
	vis[u] = true;
	low[u] = preorder[u] = ++czas;
	Q.push(u);
	naStacku[u] = true;

	for (auto& v : graf[u]) {
		if (!vis[v]) {
			DFS(v);
			low[u] = min(low[u], low[v]);
		}
		else if (naStacku[v]) {
			low[u] = min(low[u], low[v]);
		}
	}
    
	if (low[u] == preorder[u]) {
		int w = Q.top();
        // add u to component
		naStacku[u] = false;
		while (w != u) {
            // add w to component
			naStacku[w] = false;
			Q.pop();
			w = Q.top();
		}
		Q.pop();
	}
}
