int get_centroid(int root, const vector<vector<int>>& graph, const vector<bool>& dead) {
    static vector<int> roz(graph.size());

    function<void(int,int)> get_roz = [&](int u, int p) {
	    roz[u] = 1;
	    for(auto& v : graph[u]) {
	    	if(v != p and !dead[v]) {
	    		get_roz(v, u);
	    		roz[u] += roz[v];
	    	}
	    }
    };

	get_roz(root, -1);
	int cur_n = roz[root];

    function<int(int,int)> dfs = [&](int u, int p) {
	    for(auto& v : graph[u]) {
	    	if(v != p and !dead[v]) {
	    		if(roz[v] > cur_n / 2) {
	    			return dfs(v, u);
	    		}
	    	}
	    }
	    return u;
    };

	return dfs(root, -1);
}



void centroid_decomposition(const vector<vector<int>>& graph) {
    vector<bool> dead(graph.size(), false);

    function<int(int)> dfs = [&](int start) {
	    int cen = get_centroid(start, graph, dead);
	    dead[cen] = true;

	    for(auto& v : graph[cen]) {
	    	if(!dead[v]) {
	    		int sub = dfs(v);
	        }
        }
	
        // make your stuff

        // make your stuff

	    dead[cen] = false;
        return cen;
    };

	dfs(0);
}