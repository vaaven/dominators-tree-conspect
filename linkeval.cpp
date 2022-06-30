struct linkeval {
    vector<pair<int, int>> a;
    vector<int> link;

    linkeval(int n) {
        a.assign(n, make_pair(1e9, 1e9));
        link.resize(n);
        for (int i = 0; i < n; i++)
            link[i] = i;
    }

    linkeval() {}

    void unite(int v, int u) {
        get(v);
        get(v);
        if (link[v] != link[u])
            link[u] = v;
        get(u);
    }

    pair<int, int> get(int b) {
        if (link[b] == b) {
            return a[b];
        } else {
            pair<int, int> answer = get(link[b]);
            a[b] = min(answer, a[b]);
            link[b] = link[link[b]];
            return a[b];
        }
    }
};
