#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility> 

using namespace std;

// знайти дві різні вершини в кореневому дереві, що мають один колір і жодна з них не є предком іншої

const int MAXN = 2e5 + 5;

vector<int> tree[MAXN];
int tin[MAXN], tout[MAXN], timer = 0;
int color[MAXN];

void dfs(int v) {
    tin[v] = ++timer;
    for (int u : tree[v]) {
        dfs(u);
    }
    tout[v] = ++timer;
}

bool isAncestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        tree[p].push_back(i);
    }

    for (int i = 1; i <= n; ++i) {
        cin >> color[i];
    }

    dfs(1);

    unordered_map<int, vector<int>> groups;
    for (int i = 1; i <= n; ++i) {
        groups[color[i]].push_back(i);
    }

    for (auto& pair_col_nodes : groups) { 
        vector<int>& nodes = pair_col_nodes.second; 

        if (nodes.size() < 2) continue;

        sort(nodes.begin(), nodes.end(), [](int a, int b) {
            return tin[a] < tin[b];
            });

        for (int i = 0; i + 1 < (int)nodes.size(); ++i) {
            int u = nodes[i];
            int v = nodes[i + 1];

            if (!isAncestor(u, v) && !isAncestor(v, u)) {
                cout << "yes\n" << u << " " << v << "\n";
                return 0; 
            }
        }
    }

    cout << "no\n";
    return 0;
}