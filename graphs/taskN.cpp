#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

const int INF = 0x3F3F3F3F;

struct edge {
    int node, dist;
    edge(int node, int dist) : node(node), dist(dist) {}
};

bool operator< (edge a, edge b) {
    return a.dist > b.dist;
}

void Dijkstra(vector<vector<edge>>& g, vector<int>& d, vector<int>& parent, int start, int finish) {
    priority_queue<edge> pq;
    pq.push(edge(start, 0));
    d = vector<int>(g.size(), INF);
    parent = vector<int>(g.size(), -1);
    d[start] = 0;

    while (!pq.empty()) {
        edge e = pq.top();
        pq.pop();
        int v = e.node;

        if (e.dist > d[v]) continue;

        for (edge& u : g[v]) {
            int to = u.node;
            int cost = u.dist;

            if (d[v] + cost < d[to]) {
                d[to] = d[v] + cost;
                parent[to] = v; // store parent for path reconstruction
                pq.push(edge(to, d[to]));
            }
        }
    }
}

void printShortestPath(vector<int>& parent, int start, int finish) {
    stack<int> path;
    int cur = finish;
    while (cur != -1) {
        path.push(cur);
        cur = parent[cur];
    }

    cout << path.size() << endl;
    while (!path.empty()) {
        cout << path.top() << " ";
        path.pop();
    }
    cout << endl;
}

int main() {
    int n, m, start, finish;
    cin >> n >> m >> start >> finish;

    vector<vector<edge>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int b, e, w;
        cin >> b >> e >> w;
        g[b].push_back(edge(e, w));
        g[e].push_back(edge(b, w)); // if the graph is undirected
    }

    vector<int> dist, parent;
    Dijkstra(g, dist, parent, start, finish);

    if (dist[finish] == INF) {
        cout << "-1" << endl;
    } else {
        cout << dist[finish] << endl;
        printShortestPath(parent, start, finish);
    }

    return 0;
}