#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<multiset<int>> graph;
vector<int> eulerCircuit;

void dfsEuler(int node) {
    while (!graph[node].empty()) {
        int neighbor = *graph[node].begin();
        graph[node].erase(graph[node].begin());
        graph[neighbor].erase(graph[neighbor].find(node));
        dfsEuler(neighbor);
    }
    eulerCircuit.push_back(node + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int vertices;
    cin >> vertices;
    graph.resize(vertices);

    for (int i = 0; i < vertices; i++) {
        int degree;
        cin >> degree;
        for (int j = 0; j < degree; j++) {
            int vertex;
            cin >> vertex;
            vertex--;
            graph[i].insert(vertex);
        }
    }

    bool oddDegreeFound = false;
    for (int i = 0; i < vertices; i++) {
        if (graph[i].size() % 2 == 1) {
            oddDegreeFound = true;
            dfsEuler(i);
            break;
        }
    }

    if (!oddDegreeFound) {
        dfsEuler(0);
    }

    cout << eulerCircuit.size() - 1 << "\n";
    for (int node : eulerCircuit) {
        cout << node << " ";
    }
    cout << "\n";
}