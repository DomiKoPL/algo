int resultant(vi a, vi b) {
	int res = 1;
	while(true) {
		int n = SZ(a) - 1, m = SZ(b) - 1;
		if(n > m) {
			swap(n, m);
			swap(a, b);
			if(n % 2 and m % 2) {
				res = MOD - res;
			}
		}
 
		if(n == 0) {
			FOR(i, m) {
				res = mult(res, a[0]);
			}
			return res;
		}
 
		int pw = mult(b[m], invGeneral(a[n], MOD));
		FOR(i, 0, SZ(a)) {
			sub(b[SZ(b) - SZ(a) + i], mult(a[i], pw));
		}
 
		while(SZ(b) > 1 and b.back() == 0) {
			res = mult(res, a[n]);
			b.pop_back();
		}
	}
}


/*
https://codeforces.com/gym/102129/problem/G

use it to calc Determinant of cycli matrix.
[a1 a2 ... an-1 an]
[an a1 ... an-2 an-1]
...
[a3 a4 ... a1 a2]
[a2 a3 ... an a1]

b = -1 + x^n
a = (a1 a2 ... an-1 an)
Determinant = resultant(a, b)
 */
