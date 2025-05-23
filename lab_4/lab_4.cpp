#include <iostream>
#include <vector>
using namespace std;

// Задано орієнтований ациклічний граф. В графі можливі мультиребра.
// знайти кількість шляхів, які починаються в вершині a та закінчуються в вершині b


const int MOD = 1234567891;
int n, m, a, b;
vector<vector<int>> adj;
vector<int> dp;
vector<bool> visited;

int dfs(int u) {
    if (u == b) return 1; // знайшли шлях до b
    if (visited[u]) return dp[u];

    visited[u] = true;
    long long total = 0;
    for (int v : adj[u]) {
        total += dfs(v);
        if (total >= MOD) total -= MOD;
    }
    return dp[u] = total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> a >> b;
    --a; --b;

    adj.assign(n, {});
    dp.assign(n, 0);
    visited.assign(n, false);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
    }

    cout << dfs(a) << '\n';
    return 0;
}
