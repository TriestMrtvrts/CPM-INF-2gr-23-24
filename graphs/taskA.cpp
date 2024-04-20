#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // Создаем матрицу смежности, изначально заполненную нулями.
    vector<vector<int>> adjacencyMatrix(n, vector<int>(n, 0));

    // Считываем ребра и заполняем матрицу смежности.
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        // В матрице смежности ставим 1 в ячейки, соответствующие вершинам u и v.
        adjacencyMatrix[u - 1][v - 1] = 1;
        adjacencyMatrix[v - 1][u - 1] = 1; // для неориентированного графа нужно учитывать обе стороны ребра
    }

    // Выводим матрицу смежности.
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}