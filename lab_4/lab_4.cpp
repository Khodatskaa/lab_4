// Треба перевірити, чи існує шлях від верхньої лівої клітинки (0,0) до нижньої правої (n-1,m-1) через вільні клітинки 
#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long
#define INF 1e9 + 7
using namespace std;

ll n, m;

bool dfs(vector<vector<ll>>& graph, vector<bool>& visited, vector<ll>& parent, ll current, ll blockedNode) {
    visited[current] = true;
    if (current == n * m - 1) return true; 

    for (ll neighbor : graph[current]) {
        if (!visited[neighbor] && neighbor != blockedNode) {
            parent[neighbor] = current;
            if (dfs(graph, visited, parent, neighbor, blockedNode))
                return true;
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    string row;
    vector<vector<bool>> isFree(n, vector<bool>(m));   
    vector<vector<ll>> graph(n * m);
    for (ll i = 0; i < n; i++) {
        cin >> row;
        for (ll j = 0; j < m; j++) {
            isFree[i][j] = (row[j] == '.');
        }
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            if (!isFree[i][j]) continue;
            ll idx = i * m + j;

            if (i > 0 && isFree[i - 1][j])                  
                graph[idx].push_back((i - 1) * m + j);
            if (j > 0 && isFree[i][j - 1])                  
                graph[idx].push_back(i * m + (j - 1));
            if (i < n - 1 && isFree[i + 1][j])              
                graph[idx].push_back((i + 1) * m + j);
            if (j < m - 1 && isFree[i][j + 1])             
                graph[idx].push_back(i * m + (j + 1));
        }
    }

    vector<ll> parent(n * m, -1);
    vector<bool> visited(n * m, false);
    if (!dfs(graph, visited, parent, 0, -1)) {
        cout << "ZERO";
        return 0;
    }
    vector<ll> path;
    for (ll i = parent[n * m - 1]; i != -1; i = parent[i]) {
        path.push_back(i);
    }
    reverse(path.begin(), path.end());
    for (ll i = 1; i < path.size(); i++) {
        fill(visited.begin(), visited.end(), false);
        if (!(i > 2 && graph[path[i - 1]].size() <= 2 && graph[path[i]].size() <= 2)) {
            if (dfs(graph, visited, parent, 0, path[i])) {
                cout << "MANY";
                return 0;
            }
        }
    }
    cout << "ONE";
    return 0;
}