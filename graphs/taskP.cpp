#include <bits/stdc++.h>
using namespace std;

int x[5001], y[5001];
int used[5001], min_e[5001], end_e[5001];

int dist2(int i, int j) { // расстояне между вершинами i и j графа
    return (x[j] - x[i]) * (x[j] - x[i]) + (y[j] - y[i]) * (y[j] - y[i]);
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> x[i] >> y[i];

    memset(min_e, 0x3F, sizeof(min_e));
    memset(end_e, -1, sizeof(end_e));
    memset(used, 0, sizeof(used));

    double dist = min_e[1] = 0;

    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++)
            if (!used[j] && (v == -1 || min_e[j] < min_e[v])) v = j;
        used[v] = 1;
        if (end_e[v] != -1) dist += sqrt((double) dist2(v, end_e[v]));
        for (int to = 0; to < n; to++) {
            int dV_TO = dist2(v, to);
            if (!used[to] && (dV_TO < min_e[to])) {
                min_e[to] = dV_TO;
                end_e[to] = v;
            }
        }
    }

    cout << fixed << setprecision(10) << dist;
}