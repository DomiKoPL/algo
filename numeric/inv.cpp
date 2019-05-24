int invGeneral(int a, int b) { // 0 < a < b, gcd(a,b) = 1
    if (a == 0) return b == 1 ? 0 : -1;
    int x = invGeneral(b % a, a); 
    return x == -1 ? -1 : ((1 - (1ll * b * x)) / a + b) % b;
}