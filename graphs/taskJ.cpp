#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9; // Бесконечность

vector<vector<int>> adj_list; // Список смежности графа
vector<int> dist; // Массив для хранения расстояний от стартовой вершины
vector<int> parent; // Массив для хранения предков вершин в кратчайшем пути

// Функция для поиска кратчайшего пути с помощью BFS
void bfs(int s) {
    queue<int> q;
    q.push(s);
    dist[s] = 0;
    parent[s] = -1;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int u : adj_list[v]) {
            if (dist[u] == INF) {
                q.push(u);
                dist[u] = dist[v] + 1;
                parent[u] = v;
            }
        }
    }
}

// Функция для восстановления кратчайшего пути
vector<int> shortest_path(int s, int t) {
    bfs(s);

    if (dist[t] == INF) {
        return vector<int>(); // Путь не существует
    }

    vector<int> path;
    for (int v = t; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int n, m;
    cin >> n >> m;

    adj_list.resize(n);
    dist.assign(n, INF);
    parent.assign(n, -1);

    // Считываем рёбра графа
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj_list[u - 1].push_back(v - 1);
    }

    int s, t;
    cin >> s >> t;
    --s; --t;

    vector<int> path = shortest_path(s, t);

    if (path.empty()) {
        cout << "-1" << endl;
    } else {
        cout << path.size() - 1 << endl;
        for (int v : path) {
            cout << v + 1 << " ";
        }
        cout << endl;
    }

    return 0;
}