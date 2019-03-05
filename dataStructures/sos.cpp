template <typename T>
struct sos{
	vector<T>sum;
	sos(int n){
		sum.resize(1 << n);
	}

	inline void add(int mask,T val){
		sum[mask] += val;
	}

	inline void calculate{
		for(int bit = 0; bit < n; bit++){
			for(int mask = 0; mask < (1 << n); mask++){
				if(mask & (1 << bit)){
					sum[mask] += sum[mask ^ (1 << bit)];
				}
			}
		}
	}

	inline T get(int mask){
		return sum[mask];
	}
};

/*TRICK
sum[mask] - sum[mask ^ (1 << bit)] = sum of elements in group 'bit'
*/