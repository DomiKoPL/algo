template <class T> vector<int> kmp(const T& w, const T& t) {
	int n = SZ(t), m = SZ(w);
	vi p(m + 1);
	p[0] = -1;
	FOR(i, 1, m + 1) {
		p[i] = p[i - 1];
		while(p[i] != -1 and w[p[i]] != w[i - 1]) {
			p[i] = p[p[i]];
		}
		p[i]++;
	}
	vi res;
	int j = 0;
	FOR(i, 0, n) {
		while(j != -1 and w[j] != t[i]) {
			j = p[j];
		}
		if(++j == m) {
			res.PB(i - m + 1);
		}
	}
	return res;
}
