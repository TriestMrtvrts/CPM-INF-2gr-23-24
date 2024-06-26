#include<iostream>
#include<queue>
using namespace std;

int main() {
    int n, i, j, k, x1, y1, x2, y2, u, v;
    queue<pair<int, int>> q;

    // Считываем размеры доски и координаты начальной и конечной клеток
    cin >> n;
    int d[n+1][n+1];

    // Инициализируем массив расстояний очень большими значениями
    for (i = 0; i <= n; ++i)
        for (j = 0; j <= n; ++j)
            d[i][j] = 1000000000;

    cin >> x1 >> y1 >> x2 >> y2;

    // Начальная клетка имеет расстояние 0
    d[x1][y1] = 0;
    q.push(make_pair(x1, y1));

    // Начинаем BFS
    while (!q.empty()) {
        i = q.front().first;
        j = q.front().second;
        q.pop();

        // Перебираем все возможные ходы коня
        int x[8] = {-2, -2, -1, -1, 1, 1, 2, 2},
            y[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
        for (k = 0; k < 8; ++k) {
            u = i + x[k];
            v = j + y[k];

            // Проверяем, что новая клетка находится в пределах доски
            // и ее расстояние от начальной клетки больше на 1
            if (u > 0 && u <= n && v > 0 && v <= n && d[u][v] > d[i][j] + 1) {
                d[u][v] = d[i][j] + 1;
                q.push(make_pair(u, v));
            }
        }
    }

    // Выводим минимальное расстояние до конечной клетки
    cout << d[x2][y2];

    return 0;
}