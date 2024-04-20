#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool isTree(int n, int m, const vector<vector<int>>& adj_list) {
    if (m != n - 1) return false; // Проверяем количество ребер

    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(1); // Начинаем обход с вершины 1

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visited[u] = true;
        for (int v : adj_list[u]) {
            if (!visited[v]) {
                q.push(v);
            }
        }
    }

    // Проверяем, все ли вершины были достижимы из вершины 1
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) return false;
    }

    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj_list(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u); // Для неориентированного графа добавляем обратные ребра
    }

    if (isTree(n, m, adj_list)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}