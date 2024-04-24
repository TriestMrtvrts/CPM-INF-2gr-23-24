#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class SegmentTree {
 private:
    int n;
    vector<int> tree, lazy;

 public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build_tree(arr, 1, 0, n - 1);
    }

    void build_tree(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build_tree(arr, 2 * node, start, mid);
            build_tree(arr, 2 * node + 1, mid + 1, end);
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void update_range(int node, int start, int end, int left, int right, int value) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (start > right || end < left) {
            return;
        }

        if (start >= left && end <= right) {
            tree[node] += value;
            if (start != end) {
                lazy[2 * node] += value;
                lazy[2 * node + 1] += value;
            }
            return;
        }

        int mid = (start + end) / 2;
        update_range(2 * node, start, mid, left, right, value);
        update_range(2 * node + 1, mid + 1, end, left, right, value);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    int query(int node, int start, int end, int left, int right) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (start > right || end < left) {
            return numeric_limits<int>::min();
        }

        if (start >= left && end <= right) {
            return tree[node];
        }

        int mid = (start + end) / 2;
        int left_value = query(2 * node, start, mid, left, right);
        int right_value = query(2 * node + 1, mid + 1, end, left, right);
        return max(left_value, right_value);
    }
};

int main() {
    int N, M;
    cin >> N;
    vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    SegmentTree seg_tree(arr);

    cin >> M;
    vector<int> results;

    for (int i = 0; i < M; ++i) {
        char query_type;
        cin >> query_type;

        if (query_type == 'm') {
            int left, right;
            cin >> left >> right;
            results.push_back(seg_tree.query(1, 0, N - 1, left - 1, right - 1));
        } else if (query_type == 'a') {
            int left, right, add_value;
            cin >> left >> right >> add_value;
            seg_tree.update_range(1, 0, N - 1, left - 1, right - 1, add_value);
        }
    }

    for (int result : results) {
        cout << result << " ";
    }

    return 0;
}