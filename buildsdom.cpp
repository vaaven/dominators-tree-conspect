linkeval lnk;

void buildsdom(int v) {
    for (int i: gr[v]) {
        if (tin[i] > tin[v]) {
            sdom[v] = min(sdom[v], lnk.get(i));
        }
        sdom[v] = min(sdom[v], make_pair(tin[i], i));
    }

    lnk.a[v] = sdom[v];
    for (int i: g[v]) {
        if (tin[v] < tin[i])
            lnk.unite(v, i);
    }
}
