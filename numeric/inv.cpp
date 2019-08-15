template <class T> T invGeneral(T a, T b) { // 0 < a < b, gcd(a,b) = 1
    a %= b;
    if (a == 0) return b == 1 ? 0 : -1;
    T x = invGeneral(b, a); 
    return x == -1 ? -1 : ((1-(ll)b * x) / a + b) % b;
}