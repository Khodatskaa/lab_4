#include <iostream>
#include <queue>
using namespace std;

// визначити кількість мертвих клітинок через m хвилин

struct Event {
    int time;
    int x, y;
    bool operator<(const Event& other) const {
        return time > other.time; 
    }
};

const int MAXN = 100;
int n;
long long m;
int a[MAXN][MAXN];
bool visited[MAXN][MAXN];
bool dead[MAXN][MAXN];
const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> a[i][j];

    priority_queue<Event> pq;
    visited[0][0] = true;
    pq.push({ a[0][0], 0, 0 });

    int deadCount = 0;

    while (!pq.empty()) {
        Event cur = pq.top();
        pq.pop();

        if (cur.time > m) continue;

        int x = cur.x, y = cur.y;
        if (dead[x][y]) continue;

        dead[x][y] = true;
        ++deadCount;

        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx >= 0 && ny >= 0 && nx < n && ny < n && !visited[nx][ny]) {
                visited[nx][ny] = true;
                pq.push({ cur.time + a[nx][ny], nx, ny });
            }
        }
    }

    cout << deadCount << '\n';
    return 0;
}
