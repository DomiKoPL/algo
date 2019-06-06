namespace matrix {
#define TCT template <class T>
TCT T add(const T& a, const T& b) {return (a + b); } //! do it
TCT T mul(const T& a, const T& b) {return (a * b); } //! do it

TCT struct Matrix {
vector<vector<T>> a;
int n, m;
Matrix() {}
Matrix(int _n, int _m) : n(_n) , m(_m) {
	a.resize(n, vector<T>(m, 0));
}

Matrix(const vector<vector<T>>& v) : Matrix(sz(v), sz(v[0])) {
	FOR(i, 0, n - 1) FOR(j, 0, m - 1) a[i][j] = v[i][j];
}

Matrix operator+(const Matrix& o) {
	Matrix res(n, m);
	FOR(i, 0, n - 1) FOR(j, 0, m - 1)
		res.a[i][j] = add(res.a[i][j], o.a[i][j]);
	return res;
}

Matrix operator*(const Matrix& o) {
	Matrix res(n, o.m);
	FOR(i, 0, n - 1) FOR(j, 0, m - 1) FOR(k, 0, o.m - 1)
		res.a[i][k] = add(res.a[i][k], mul(a[i][j], o.a[j][k]));
	return res;
}

Matrix operator^(ll k) {
	Matrix res(n, n), a{*this};
	FOR(i, 0, n - 1) res.a[i][i] = 1;
	for(; k; k >>= 1) {
		if(k & 1) res = res * a;
		a = a * a;
	}
	return res;
}
};
#undef TCT
}
using namespace matrix;