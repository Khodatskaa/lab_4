#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;

vector<int> tree[MAXN];
int depth[MAXN], sz[MAXN];
long long total_depth = 0;

void dfs(int v, int parent) {
    sz[v] = 1;
    for (int u : tree[v]) {
        if (u == parent) continue;
        depth[u] = depth[v] + 1;
        dfs(u, v);
        sz[v] += sz[u];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs(1, -1);

    long long original_sum = 0;
    for (int i = 1; i <= n; ++i) {
        original_sum += depth[i];
    }

    long long max_gain = 0;

    for (int u = 2; u <= n; ++u) {
        long long new_depth = 1;
        long long delta = (new_depth - depth[u]) * 1LL * sz[u];
        max_gain = max(max_gain, -delta); 
    }

    cout << original_sum - max_gain << "\n";
    return 0;
}
