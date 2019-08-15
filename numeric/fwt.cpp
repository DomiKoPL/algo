template <typename T, typename F> 
void  fwt (T a[], int n, F f)  {
	for(int d = 1; d < n; d *= 2) {
		for(int i = 0, t = d * 2; i < n; i += t) {
			for(int j = 0; j < d; j++) {
				f(a[i + j], a[i + j + d]);
			}
		}
	}
}
   
void XOR(ll& a, ll& b)  {
    ll x = a, y = b;
    a = (x + y) % MOD;
    b = (x - y + MOD) % MOD;
}

void OR(ll& a, ll& b) {
    ll x = a, y = b;
    a = (x) % MOD;
    b = (x + y) % MOD;
}

/*
    ! C[k] = SUM A[i] * B[j] : g(i, j) = k
    
    * C = f(A, B)
    * 
    * XOR:
    * C0 = f(A0, B0) + f(A1, B1)
    * C1 = f(A0, B1) + f(A1, B0)
    * 
    * C0 + C1 = ... = f(A0 + B0, A1 + B1)
    * C0 - C1 = ... = f(A0 - B0, A1 - B1)
    * 
    * (C0 + C1) :: (C0 - C1) = f(A0 + B0, A1 + B1) ::
    *                           f(A0 - B0, A1 - B1)
    * 
    * FWT(A) = FWT(A0 :: A1) = FWT(A0 + A1) :: FWT(A0 - A1)
    * 
    * FWT(C) = FWT(A) · FWT(B)
    * 
    * C = FWT^-1(FWT(C)) = FWT^-1(FWT(A) * FWT(B))
    * 
    * FWT^-1(A) = FWT(A) / n
    * 
    *  algo:
    *  fwt(A, f)
    *  fwt(B, f)
    *  for each i: C[i] = A[i] * B[i]
    *  fwt(C, f^-1) 
    * 
    *  example task:
    *  https://codeforces.com/gym/102129/problem/A
    * 
    *  write:
    * c0 = a1 * b1 + a1 * b2 + a2 * b1 + a2 * b2
    * c1 = a0 * b2 + a2 * b0 + a0 * b0
    * c2 = a0 * b1 + a1 * b0
    * 
    * now solve to shape ci = (ax + .. + ay) * (bx + .. + by)
    * 
    * sometimes we need to add new equation
    * in this example we need to add:
    * c3 = a2 * b2
    * 
    * now we can write:
    * c0 = (a1 + a2) * (b1 + b2)
    * c0 + c1 + c2 = (a0 + a1 + a2) * (b0 + b1 + b2)
    * c1 + c3 = (a0 + a2) * (b0 + b2)
    * c3 = (a2) * (b2)
    * 
    * now we must make a function f
    * that go from a0, a1, a2, a3 to a0', a1', a2', a3'
    * f( a,  b,  c, d)
    *   x0, x1, x2, x3
    *  a  = x1 + x2
    *  b = x0 + x1 + x2
    *  c = x0 + x2
    *  d = x2
    * 
    * and now make a reverse function to f
    * that go from a0, a1, a2, a3 to c0, c1, c2
    * f^-1( a,  b,  c, d)
    *   x0, x1, x2, x3
    *  a = x0
    *  b = x2 - x3
    *  c = x1 - x0 - x2 + x3
 */