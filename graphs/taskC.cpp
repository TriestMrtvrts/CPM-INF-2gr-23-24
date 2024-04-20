#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    // Считываем матрицу смежности.
    vector<vector<int>> adjacencyMatrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> adjacencyMatrix[i][j];
        }
    }

    vector<int> sources; // вершины-истоки
    vector<int> sinks;   // вершины-стоки

    // Проверяем каждую вершину на то, является ли она истоком или стоком.
    for (int i = 0; i < n; ++i) {
        bool isSource = true;
        bool isSink = true;
        for (int j = 0; j < n; ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                isSource = false;
            }
            if (adjacencyMatrix[j][i] == 1) {
                isSink = false;
            }
        }
        if (isSource) {
            sources.push_back(i + 1); // добавляем вершину (индекс + 1) в список истоков
        }
        if (isSink) {
            sinks.push_back(i + 1); // добавляем вершину (индекс + 1) в список стоков
        }
    }

    // Выводим количество и список вершин-стоков.
    cout << sinks.size() << endl;
    for (int sink : sinks) {
        cout << sink << " ";
    }
    cout << endl;
    // Выводим количество и список вершин-истоков.
    cout << sources.size() << endl;
    for (int source : sources) {
        cout << source << " ";
    }
    cout << endl;


    return 0;
}