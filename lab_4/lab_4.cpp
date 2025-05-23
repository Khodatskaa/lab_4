#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <string>
#include <cmath>
#include <limits>
using namespace std;

// Потрібно визначити, чи можна дістатися з однієї станції до іншої, прокладаючи нові рейки не довші за $k$, і якщо так — за яку мінімальну кількість днів.

const int INF = numeric_limits<int>::max();

struct Station {
    string name;
    int x, y;
};

int distance_squared(const Station& a, const Station& b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    string s1, s2;
    cin >> s1 >> s2;

    map<string, int> name_to_id;
    vector<Station> stations(n);
    for (int i = 0; i < n; ++i) {
        cin >> stations[i].name >> stations[i].x >> stations[i].y;
        name_to_id[stations[i].name] = i;
    }

    vector<vector<pair<int, int>>> graph(n);

    for (int i = 0; i < m; ++i) {
        string u, v;
        cin >> u >> v;
        int a = name_to_id[u];
        int b = name_to_id[v];
        graph[a].push_back({ b, 0 });
        graph[b].push_back({ a, 0 });
    }

    int k2 = k * k;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (distance_squared(stations[i], stations[j]) <= k2) {
                graph[i].push_back({ j, 1 });
                graph[j].push_back({ i, 1 });
            }

    int start = name_to_id[s1], goal = name_to_id[s2];
    vector<int> dist(n, INF);
    deque<int> dq;
    dq.push_back(start);
    dist[start] = 0;

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (auto [v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0)
                    dq.push_front(v);
                else
                    dq.push_back(v);
            }
        }
    }

    if (dist[goal] == INF) {
        cout << "NO\n";
    }
    else {
        cout << "YES\n" << dist[goal] << '\n';
    }

    return 0;
}
