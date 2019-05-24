bool vis[N];
bool punktAr[N]; //czy v jest pukntem artykulacji
int licznik = 1, iloscDzieciKorzenia = 0;
int korzen;

void DFS(int v, int ojciec) {
	vis[v] = true;
	preOrder[v] = licznik++;
	low[v] = licznik++;
	for (int i = 0; i < (int)graf[v].size(); i++) {
		int u = graf[v][i];
		if (u != ojciec) {
			if (vis[u]) {
				low[v] = min(low[v], preOrder[u]);
			}
			else {
				if (v == korzen) {
					if (++iloscDzieciKorzenia == 2) {
						punktAr[korzen] = true;
					}
				}

				DFS(u, v);
				low[v] = min(low[v], low[u]);
				if (low[u] >= preOrder[v] && v != korzen) {
                    punktAr[v] = true;
				}
			}
		}
	}
}