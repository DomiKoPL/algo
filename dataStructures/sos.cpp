template <typename T> struct SOS { // sum over subset
	vector<T>sum;
	int n;

	SOS(int n) : n(n) {
		sum.resize(1 << n);
	}

	void add(int mask, T val) {
		sum[mask] += val;
	}

	void calculate() {
		for(int bit = 0; bit < n; bit++) {
			for(int mask = 0; mask < (1 << n); mask++){
				if(mask & (1 << bit)) {
					sum[mask] += sum[mask ^ (1 << bit)];
				}
			}
		}
	}

	T get(int mask) {
		return sum[mask];
	}
};

/*TRICK
sum[mask] - sum[mask ^ (1 << bit)] = sum of elements in group 'bit'
*/