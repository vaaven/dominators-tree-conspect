#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <math.h>

#define pb(x) push_back(x)
#define endl '\n'
#define all(x) x.begin(), x.end()
#define int long long

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pair<int, int>> vpii;

const ll inf = 1e9 + 228;
const int maxn = 2e5 + 228;

struct linkeval {
    vpii a;
    vi link;

    linkeval(int n) {
        a.resize(n);
        for (pii &i: a)
            i = make_pair(inf, inf);
        link.resize(n);
        for (int i = 0; i < n; i++)
            link[i] = i;
    }

    linkeval() {}

    void unite(int aa, int b) {
        get(aa);
        get(b);
        if (link[aa] != link[b])
            link[b] = aa;
        get(b);
    }

    pii get(int b) {
        if (link[b] == b) {
            return a[b];
        } else {
            pii ans = get(link[b]);
            a[b] = min(ans, a[b]);
            link[b] = link[link[b]];
            return a[b];
        }
    }

};

vi g[maxn];
vi gr[maxn];
int tin[maxn];
int tout[maxn];
pii sdom[maxn];
bool used[maxn];
int up[maxn][18];
int d[maxn][18];
int idom[maxn];
vi g2[maxn];
int timer = 0;
ll ans = 0;
vpii lol;
linkeval kek;

void dfs(int v) {
    tin[v] = timer++;
    used[v] = true;
    for (int i: g[v]) {
        if (!used[i]) {
            dfs(i);
        }
    }
    lol.pb(make_pair(tin[v], v));
    tout[v] = timer++;
}

void buildsdom(int v) {
    for (int i: gr[v]) {
        if (tin[i] > tin[v]) {
            sdom[v] = min(sdom[v], kek.get(i));
        }
        sdom[v] = min(sdom[v], make_pair(tin[i], i));
    }
    kek.a[v] = sdom[v];
    for (int i: g[v]) {
        if (tin[v] < tin[i])
            kek.unite(v, i);
    }
}

bool upper(int a, int b) {
    return tin[a] < tin[b] && tout[b] < tout[a];
}

void dfs2(int v, int p = 0) {
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
            dfs2(i, v);
}

ll dfs3(int v, int p = -1) {
    int sum = 1;
    ll ans = 0;
    used[v] = true;
    for (int i: g2[v]) {
        if (!used[i]) {
            int lol = dfs3(i, v);
            ans += sum * 1ll * lol;
            sum += lol;
        }
    }
    if (!v) {
        ::ans = ans;
    }
    return sum;
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        gr[b].pb(a);
        g[a].pb(b);
    }
    fill(tin, tin + maxn, inf);
    for (int i = 0; i < n; i++) {
        if (!used[i])
            dfs(i);
    }
    for (int i = 0; i < n; i++) {
        sdom[i] = make_pair(tin[i], i);
    }
    sort(all(lol));
    reverse(all(lol));
    kek = linkeval(n);
    for (auto & i : lol) {
        buildsdom(i.second);
    }
    fill(used, used + maxn, false);
    fill(idom, idom + maxn, -1);
    reverse(all(lol));
    for (pii i: lol) {
        if (!used[i.second])
            dfs2(i.second);
    }
    for (int i = 0; i < n; i++) {
        if (idom[i] != -1) {
            g2[idom[i]].pb(i);
        }
    }
    fill(used, used + maxn, false);
    dfs3(0);
    cout << ans << endl;
}

signed main() {
    int q = 1;
    while (q--)
        solve();
    return 0;
}
