
template <typename T>
struct Flow {
	vector<vector<T> > capacity;
	vector<vector<int> > graf;
	vector<int> vis, ojciec;
	int TIME = 1;
	long long INF = 1e11 + 7; // zmienic

	Flow(int n) {
		capacity.resize(n,vector<T>(n));
		graf.resize(n,vector<int>());
		vis.resize(n,0);
		ojciec.resize(n,0);
	}

	void addEdge(int a,int b,T cap) {
		graf[a].push_back(b);
		capacity[a][b] = cap;
	}

	void addEdge2(int a, int b, T cap) {
		graf[a].push_back(b);
		capacity[a][b] = cap;

		graf[b].push_back(a);
		capacity[b][a] = 0;
	}

	int bfs(int start,int koniec) {
		TIME++;

		ojciec[start] = -2;
		vis[start] = TIME;

		queue<pair<int,T> >Q;
		Q.push({ start,INF });

		while (Q.size()) {
			int u = Q.front().first;
			T flow = Q.front().second;
			Q.pop();

			for (auto& v : graf[u]) {
				if (vis[v] != TIME and capacity[u][v] > 0) {
					vis[v] = TIME;
					ojciec[v] = u;

					T temp = min(flow, capacity[u][v]);

					if (v == koniec) {
						return temp;
					}

					Q.push({ v, temp });
				}
			}
		}

		return 0;
	}

	T maxFlow(int start,int koniec) {
		T flow = 0, curFlow;

		while (curFlow = bfs(start, koniec)) {
			flow += curFlow;
			int ob = koniec;

			while (ob != start){
				int poprz = ojciec[ob];

				capacity[poprz][ob] -= curFlow;
				capacity[ob][poprz] += curFlow;

				ob = poprz;
			}
		}

		return flow;
	}
};