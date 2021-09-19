ll ccw(pii const& a, pii const& b, pii const& c) {
    return 1ll * a.first * (b.second - c.second) +
            1ll * b.first * (c.second - a.second) +
            1ll * c.first * (a.second - b.second);
} 

vpii make_hull(vpii points) {
    if(SZ(points) == 1) { return points; }
    vpii hull;
    hull.reserve(SZ(points) + 1);
    sort(ALL(points));
    FOR(phase, 0, 2) {
        auto start = SZ(hull);
        TRAV(point, points) {
            while(SZ(hull) >= start + 2 and ccw(hull[SZ(hull) - 2], hull.back(), point) <= 0)
                hull.pop_back();
            hull.push_back(point); 
        }
        hull.pop_back();
        REV(points);
    }
    if(SZ(hull) == 2 and hull[0] == hull[1]) hull.pop_back();
    return hull;
}   
