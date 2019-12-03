namespace matrix {
	#define TCT template <class T>
	TCT T add(const T& a, const T& b) {return (a + b); } //! do it
	TCT T mul(const T& a, const T& b) {return (a * b); } //! do it

	TCT struct Matrix {
		vector<vector<T>> a;
		int n, m;
		Matrix() {}
		Matrix(int n, int m) : n(n) , m(m) {
			a.resize(n, vector<T>(m, 0));
		}

		Matrix(const vector<vector<T>>& v) : Matrix(SZ(v), SZ(v[0])) {
			FOR(i, 0, n) FOR(j, 0, m) a[i][j] = v[i][j];
		}

		Matrix operator+(const Matrix& o) const {
			Matrix res(n, m);
			FOR(i, 0, n) FOR(j, 0, m)
				res.a[i][j] = add(a[i][j], o.a[i][j]);
			return res;
		}

		Matrix operator*(const Matrix& o) const {
			Matrix res(n, o.m);
			FOR(i, 0, n) FOR(k, 0, o.m) FOR(j, 0, m)
				res.a[i][k] = add(res.a[i][k], mul(a[i][j], o.a[j][k]));
			return res;
		}

		Matrix operator^(ll k) const {
			Matrix res(n, n), a{*this};
			FOR(i, 0, n) res.a[i][i] = 1;
			for(; k; k >>= 1) {
				if(k & 1) res = res * a;
				a = a * a;
			}
			return res;
		}
	};
	#undef TCT
} // namespace matrix