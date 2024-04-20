#include <iostream>
#include <cstring>
#include <vector>

const int MAX = 110;

int g[MAX][MAX], used[MAX];
int Error = 0;
std::vector<int> cheaters;

void dfs(int v, int color, int n) {
    if (Error) return;
    used[v] = color;
    for (int i = 1; i <= n; i++) {
        if (g[v][i]) {
            if (!used[i]) {
                dfs(i, 3 - color, n);
            } else if (used[v] == used[i]) {
                Error = 1;
            }
        }
    }
}

int main() {
    int n, m, a, b;
    std::cin >> n >> m;
    memset(g, 0, sizeof(g));
    memset(used, 0, sizeof(used));
    for (int i = 0; i < m; i++) {
        std::cin >> a >> b;
        g[a][b] = g[b][a] = 1;
    }
    Error = 0;
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs(i, 1, n);
        }
    }
    if (Error) {
        std::cout << "NO\n";
    } else {
        std::cout << "YES\n";
        for (int i = 1; i <= n; i++) {
            if (used[i] == 1) {
                cheaters.push_back(i);
            }
        }
        std::cout << cheaters.size() << "\n";
        for (int i = 0; i < cheaters.size(); i++) {
            std::cout << cheaters[i] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}