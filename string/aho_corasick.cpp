struct aho_corasick {
	static const int K = 26;
	struct Vertex {
			int next[K];
			int leaf = 0, count = -1;
			int p = -1;
			char pch;
			int link = -1;
			int go[K];
 
			Vertex(int p=-1, char ch='$') : p(p), pch(ch) {
					fill(begin(next), end(next), -1);
					fill(begin(go), end(go), -1);
			}
	};
 
	vector<Vertex> t;
	aho_corasick() {
		t.push_back(Vertex());
	}
 
	void add_string(string const& s) {
			int v = 0;
			for (char ch : s) {
					int c = ch - 'a';
					if (t[v].next[c] == -1) {
							t[v].next[c] = t.size();
							t.emplace_back(v, ch);
					}
					v = t[v].next[c];
			}
			t[v].leaf++;
	}
 
	int calc(int v) {
		if (v == 0)
			return 0;
		if (t[v].count == -1)
			t[v].count = t[v].leaf + calc(get_link(v));
		return t[v].count;
	}
 
	void calc() {
		t[0].count = 0;
		for (int v = 1; v < sz(t); v++) {
			calc(v);
		}
	}
 
	int get_link(int v) {
			if (t[v].link == -1) {
					if (v == 0 || t[v].p == 0)
							t[v].link = 0;
					else
							t[v].link = go(get_link(t[v].p), t[v].pch);
			}
			return t[v].link;
	}
 
	int go(int v, char ch) {
			int c = ch - 'a';
			if (t[v].go[c] == -1) {
					if (t[v].next[c] != -1)
							t[v].go[c] = t[v].next[c];
					else
							t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
			}
			return t[v].go[c];
	}
};