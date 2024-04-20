#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void dfs(int v, const vector<vector<int>>& adj_list, vector<bool>& visited, unordered_set<int>& component) {
    visited[v] = true;
    component.insert(v);
    for (int u : adj_list[v]) {
        if (!visited[u]) {
            dfs(u, adj_list, visited, component);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj_list(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u); // для неориентированного графа добавляем обратные ребра
    }

    vector<bool> visited(n + 1, false);
    vector<unordered_set<int>> components;

    for (int v = 1; v <= n; ++v) {
        if (!visited[v]) {
            unordered_set<int> component;
            dfs(v, adj_list, visited, component);
            components.push_back(component);
        }
    }

    cout << components.size() << endl;
    for (const auto& component : components) {
        cout << component.size() << endl;
        for (int v : component) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}