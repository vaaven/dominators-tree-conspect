bool upper(int a, int b) {
    return tin[a] < tin[b] && tout[b] < tout[a];
}

void buildidom(int v, int p = 0) {
    if (v) {
        up[v][0] = p, d[v][0] = v;
        for (int i = 1; i < 18; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
            if (sdom[d[v][i - 1]].first < sdom[d[up[v][i - 1]][i - 1]].first)
                d[v][i] = d[v][i - 1];
            else
                d[v][i] = d[up[v][i - 1]][i - 1];
        }
        int ans = v, cur = v;
        for (int i = 17; i >= 0; i--) {
            if (!upper(up[cur][i], sdom[v].second)) {
                if (sdom[ans].first > sdom[d[cur][i]].first)
                    ans = d[cur][i];
                cur = up[cur][i];
            }
        }
        if (sdom[ans].second == sdom[v].second)
            idom[v] = sdom[v].second;
        else
            idom[v] = idom[ans];
    }
    used[v] = true;
    for (int i: g[v])
        if (!used[i])
            buildidom(i, v);
}
