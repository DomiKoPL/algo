vector<pii> graf[N];// ->v , id
int lastWE[N], euler[2 * N]; 
// lastWE[i] - last x that euler[x] = i
// euler[i] - ith edge in euler tour
void makeEulerTour(int u, int p = -1) {
	for (auto& kr : graf[u]) {
		int v = kr.first; // v = vertex
		if (v != p) {
			euler[id++] = kr.second;
			makeEulerTour(v, u);
			euler[id++] = kr.second;
		}
	}
	lastWE[u] = id;
}