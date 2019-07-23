... add some queries
    kubelki[pocz / SQRT].push_back(Zap(pocz, kon, t));

for (int kub = 0; kub < SQRT; kub++) {
    if (kubelki[kub].size() == 0u)continue;
    sort(kubelki[kub].begin(), kubelki[kub].end());
    // we can do better sort in kub % 2 == 0 in < order
    // and in kub % 2 == 1 in > order

    int l = kubelki[kub][0].l, p = kubelki[kub][0].p;
    int id = kubelki[kub][0].id;

    for (int i = l; i <= p; i++)add(i);
    res[id] = ...

    for (int j = 1; j < kubelki[kub].size(); j++) {
        int nl = kubelki[kub][j].l, np = kubelki[kub][j].p;
        id = kubelki[kub][j].id;
        while (nl < l)add(--l);
        while (nl > l)del(l++);
        while (np > p)add(++p);
        while (np < p)del(p--);
        res[id] = ...
    }
}