#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const long long INF = 1e18;
const int MAXN = 200005;

vector<pair<int, int>> graph[MAXN];
long long dist[MAXN];

void dijkstra(int start, int n) {
    for (int i = 1; i <= n; ++i)
        dist[i] = INF;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[start] = 0;
    pq.push({ 0, start });

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (auto [v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({ dist[v], v });
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q, c;
    cin >> n >> m >> q >> c;

    for (int i = 0; i < m; ++i) {
        int x, y, d;
        cin >> x >> y >> d;
        graph[x].emplace_back(y, d);
        graph[y].emplace_back(x, d);
    }

    dijkstra(c, n);

    for (int i = 0; i < q; ++i) {
        int v, u;
        cin >> v >> u;
        long long result = dist[v] + dist[u];
        cout << result << "\n";
    }

    return 0;
}
