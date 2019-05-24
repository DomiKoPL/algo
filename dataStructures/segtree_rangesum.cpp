const int treeSize = 1 << 18;
ll tree[treeSize << 1];
ll lazy[treeSize << 1];

void update(int node, int lo, int hi) {
	if (lazy[node] != 0) {
		tree[node] += (hi - lo + 1) * lazy[node];
		if (lo != hi) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		lazy[node] = 0;
	}
}

void insertTree(int a, int b, ll val, int node = 1, int lo = 0, int hi = treeSize - 1) {
	update(node, lo, hi);
	if (lo > hi || lo > b || hi < a)
		return;
	if (lo >= a && hi <= b) {
		tree[node] += (hi - lo + 1) * val;
		if (lo != hi) {
			lazy[node * 2] += val;
			lazy[node * 2 + 1] += val;
		}
		return;
	}

	int mid = lo + hi >> 1;
	insertTree(a, b, val, node << 1, lo, mid);
	insertTree(a, b, val, (node << 1) + 1, mid + 1, hi);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll getSum(int a, int b, int lo = 0, int hi = treeSize - 1, int node = 1) {
	update(node, lo, hi);
	if (lo > hi || lo > b || hi < a)
		return 0;
	if (lo >= a && hi <= b)
		return tree[node];
	int mid = (lo + hi) / 2;
	return getSum(a, b, lo, mid, 2 * node) + 
    getSum(a, b, mid + 1, hi, 2 * node + 1);
}