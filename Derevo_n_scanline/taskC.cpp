#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;

struct SegmentTree {
    int size;
    vector<int> tree;

    void initialize() {
        tree.assign(4 * size, 0);
    }

    void update(int v, int left, int right, int position) {
        tree[v]++;
        if (right == left + 1) {
            return;
        }
        int middle = (left + right) / 2;
        if (position < middle) {
            update(2 * v + 1, left, middle, position);
        } else {
            update(2 * v + 2, middle, right, position);
        }
    }

    int query(int v, int left, int right, int queryLeft, int queryRight) {
        if (left >= queryLeft && right <= queryRight) {
            return tree[v];
        } else if (left >= queryRight || right <= queryLeft) {
            return 0;
        }
        int middle = (left + right) / 2;
        return query(2 * v + 1, left, middle, queryLeft, queryRight) +
               query(2 * v + 2, middle, right, queryLeft, queryRight);
    }
};

int lowerBound(vector<int> &arr, int value, int left, int right) {
    if (right == left + 1) {
        return left + (arr[right] <= value);
    }
    int middle = (right + left) / 2;
    if (value > arr[middle]) {
        return lowerBound(arr, value, middle, right);
    }
    return lowerBound(arr, value, left, middle);
}

int upperBound(vector<int> &arr, int value, int left, int right) {
    if (right == left + 1) {
        return right - (arr[left] >= value);
    }
    int middle = (right + left) / 2;
    if (value >= arr[middle]) {
        return upperBound(arr, value, middle, right);
    }
    return upperBound(arr, value, left, middle);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, l;
    cin >> n;

    vector<vector<int>> points(n, vector<int>(4));

    for (int i = 0; i < n; i++) {
        cin >> points[i][0] >> points[i][2];
        points[i][1] = 0;
    }

    vector<int> uniquePoints(n);
    for (int i = 0; i < n; i++) {
        uniquePoints[i] = points[i][2];
    }

    sort(uniquePoints.begin(), uniquePoints.end());
    uniquePoints.erase(unique(uniquePoints.begin(), uniquePoints.end()), uniquePoints.end());
    l = uniquePoints.size();

    int m;
    cin >> m;

    vector<int> result(m, 0);

    points.resize(n + 2 * m, vector<int>(4));

    for (int i = 0; i < n; i++) {
        points[i][2] = lowerBound(uniquePoints, points[i][2], -1, l - 1);
    }

    for (int i = 0; i < m; i++) {
        cin >> points[n + 2 * i][0] >> points[n + 2 * i][2];
        points[n + 2 * i][1] = -(i + 1);
        points[n + 2 * i][2] = upperBound(uniquePoints, points[n + 2 * i][2], 0, l);
        cin >> points[n + 2 * i + 1][0] >> points[n + 2 * i + 1][2];
        points[n + 2 * i + 1][1] = i + 1;
        points[n + 2 * i + 1][2] = lowerBound(uniquePoints, points[n + 2 * i + 1][2], -1, l - 1);
        points[n + 2 * i][3] = points[n + 2 * i + 1][2];
        points[n + 2 * i + 1][3] = points[n + 2 * i][2];
    }

    sort(points.begin(), points.end());

    SegmentTree segmentTree;
    segmentTree.size = l;
    segmentTree.initialize();

    for (int i = 0; i < n + 2 * m; i++) {
        if (points[i][1] == 0) {
            segmentTree.update(0, 0, l, points[i][2]);
        } else if (points[i][1] < 0) {
            result[-points[i][1] - 1] -= segmentTree.query(0, 0, l, points[i][2], points[i][3] + 1);
        } else {
            result[points[i][1] - 1] += segmentTree.query(0, 0, l, points[i][3], points[i][2] + 1);
        }
    }

    for (int i = 0; i < m; i++) {
        cout << result[i] << "\n";
    }

    return 0;
}