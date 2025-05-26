#include <iostream>
#include <vector>

using namespace std;

using ll = long long;
const int INF = 1e9 + 7;

void dfs(ll current, const vector<vector<ll>>& graph, vector<bool>& visited, ll root, ll parent) {
    if (parent != root)
        cout << root + 1 << " " << parent + 1 << " " << current + 1 << "\n";

    visited[current] = true;

    for (ll neighbor : graph[current]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited, root, current);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    vector<vector<ll>> graph(n);
    vector<bool> visited(n, false);

    for (ll i = 0; i < n - 1; ++i) {
        ll u, v;
        cin >> u >> v;
        --u; --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    ll maxDegree = 0, center = 0;
    for (ll i = 0; i < n; ++i) {
        if (graph[i].size() > maxDegree) {
            maxDegree = graph[i].size();
            center = i;
        }
    }

    cout << (n - 1 - maxDegree) << "\n";

    dfs(center, graph, visited, center, center);

    return 0;
}