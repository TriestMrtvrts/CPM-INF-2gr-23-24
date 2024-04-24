#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;

struct SegmentTree {
    int n;
    vector<int> tree;
    vector<int> lazy;

    void initialize() {
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void push(int v, int l, int r) {
        lazy[2 * v + 1] += lazy[v];
        lazy[2 * v + 2] += lazy[v];
        tree[2 * v + 1] += lazy[v];
        tree[2 * v + 2] += lazy[v];
        lazy[v] = 0;
    }

    void update(int v, int l, int r, int l1, int r1, int val) {
        if (l >= r1 || r <= l1) {
            return;
        }
        if (l >= l1 && r <= r1) {
            tree[v] += val;
            lazy[v] += val;
            return;
        }
        push(v, l, r);
        int m = (r + l) / 2;
        update(2 * v + 1, l, m, l1, r1, val);
        update(2 * v + 2, m, r, l1, r1, val);
        tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
    }

    int query(int v, int l, int r) {
        if (l + 1 == r) {
            return l;
        }
        push(v, l, r);
        int m = (r + l) / 2;
        if (tree[v] > tree[2 * v + 1]) {
            return query(2 * v + 2, m, r);
        }
        return query(2 * v + 1, l, m);
    }
};

int main() {
    SegmentTree st;
    int n;
    cin >> n;
    st.n = 2 * 1e6 + 10;
    st.initialize();
    vector<vector<int>> rectangles(2 * n, vector<int>(4));
    for (int i = 0; i < n; i++) {
        cin >> rectangles[2 * i][2] >> rectangles[2 * i][0] >> rectangles[2 * i][3] >> rectangles[2 * i + 1][0];
        rectangles[2 * i + 1][2] = rectangles[2 * i][3];
        rectangles[2 * i + 1][3] = rectangles[2 * i][2];
        rectangles[2 * i][1] = -1;
        rectangles[2 * i + 1][1] = 1;
        rectangles[2 * i][0] += 1e6;
        rectangles[2 * i][2] += 1e6;
        rectangles[2 * i][3] += 1e6;
        rectangles[2 * i + 1][0] += 1e6;
        rectangles[2 * i + 1][2] += 1e6;
        rectangles[2 * i + 1][3] += 1e6;
    }
    sort(rectangles.begin(), rectangles.end());
    int maxArea = 0, left = -1, right;
    for (int i = 0; i < 2 * n; i++) {
        if (rectangles[i][1] == -1) {
            st.update(0, 0, st.n, rectangles[i][2], rectangles[i][3] + 1, 1);
        } else {
            st.update(0, 0, st.n, rectangles[i][3], rectangles[i][2] + 1, -1);
        }
        if (maxArea < st.tree[0]) {
            maxArea = st.tree[0];
            left = st.query(0, 0, st.n) - 1e6;
            right = rectangles[i][0] - 1e6;
        }
    }
    cout << maxArea << endl;
    cout << left << " " << right;
    return 0;
}