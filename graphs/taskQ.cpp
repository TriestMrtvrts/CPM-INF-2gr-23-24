#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<pair<int, int>>> graph;
vector<bool> visited;
vector<bool> is_bridge;
vector<int> discovery_time, lowest_time;
int bridge_count = 0;

void dfs(int node, int edge_id) {
    static int time = 0;
    visited[node] = true;
    discovery_time[node] = lowest_time[node] = ++time;

    for (auto [neighbour, edge] : graph[node]) {
        if (edge == edge_id) continue;
        if (!visited[neighbour]) {
            dfs(neighbour, edge);
            lowest_time[node] = min(lowest_time[node], lowest_time[neighbour]);
            if (lowest_time[neighbour] > discovery_time[node]) {
                is_bridge[edge] = true;
                bridge_count++;
            }
        } else {
            lowest_time[node] = min(lowest_time[node], discovery_time[neighbour]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    graph.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        graph[u].emplace_back(v, i);
        graph[v].emplace_back(u, i);
    }

    visited.resize(n, false);
    is_bridge.resize(m, false);
    discovery_time.resize(n);
    lowest_time.resize(n);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, -1);
        }
    }

    vector<int> bridges;
    for (int i = 0; i < m; i++) {
        if (is_bridge[i]) bridges.push_back(i + 1);
    }

    cout << bridges.size() << '\n';
    for (int bridge : bridges) {
        cout << bridge << ' ';
    }
}