#include <bits/stdc++.h>
using namespace std;

void initFastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main() {
    initFastIO();

    int rows, cols;
    cin >> rows >> cols;
    vector<vector<int>> distance(rows, vector<int>(cols, 0));
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    deque<pair<int, int>> queue;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int cellValue;
            cin >> cellValue;
            if (cellValue == 1) {
                queue.emplace_back(row, col);
                visited[row][col] = true;
            }
        }
    }

    while (!queue.empty()) {
        auto [curRow, curCol] = queue.front();
        queue.pop_front();
        for (auto [dRow, dCol] : directions) {
            int newRow = curRow + dRow, newCol = curCol + dCol;
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && !visited[newRow][newCol]) {
                visited[newRow][newCol] = true;
                distance[newRow][newCol] = distance[curRow][curCol] + 1;
                queue.emplace_back(newRow, newCol);
            }
        }
    }

    for (auto &rowDistances : distance) {
        for (int d : rowDistances)
            cout << d << " ";
        cout << '\n';
    }
}