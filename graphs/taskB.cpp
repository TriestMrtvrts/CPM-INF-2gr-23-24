#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // Создаем вектор, чтобы хранить степени вершин. Изначально все степени устанавливаем в 0.
    vector<int> degrees(n, 0);

    // Считываем ребра и увеличиваем степени соответствующих вершин.
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        // Увеличиваем степени вершин u и v.
        degrees[u - 1]++;
        degrees[v - 1]++;
    }

    // Выводим степени вершин.
    for (int degree : degrees) {
        cout << degree << endl;
    }

    return 0;
}