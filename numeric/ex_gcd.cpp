struct EGCD { ll x, y, d; };
EGCD exGCD(ll a, ll b) {
    if(b == 0) return {1, 0, a};
    auto r = exGCD(b, a % b);
    return {r.y, r.x - a / b * r.y, r.d};
}