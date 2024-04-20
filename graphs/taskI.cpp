#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void dfs1(int v, const vector<vector<int>>& adj_list, vector<bool>& visited, stack<int>& st) {
    visited[v] = true;
    for (int u : adj_list[v]) {
        if (!visited[u]) {
            dfs1(u, adj_list, visited, st);
        }
    }
    st.push(v);
}

void dfs2(int v, const vector<vector<int>>& adj_list_t, vector<bool>& visited, vector<int>& comp, int comp_num) {
    visited[v] = true;
    comp[v] = comp_num;
    for (int u : adj_list_t[v]) {
        if (!visited[u]) {
            dfs2(u, adj_list_t, visited, comp, comp_num);
        }
    }
}

vector<int> kosaraju(int n, const vector<vector<int>>& adj_list, const vector<vector<int>>& adj_list_t) {
    vector<bool> visited(n, false);
    stack<int> st;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs1(i, adj_list, visited, st);
        }
    }

    fill(visited.begin(), visited.end(), false);
    vector<int> comp(n, -1);
    int comp_num = 0;

    while (!st.empty()) {
        int v = st.top();
        st.pop();
        if (!visited[v]) {
            dfs2(v, adj_list_t, visited, comp, comp_num);
            ++comp_num;
        }
    }

    return comp;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj_list(n);
    vector<vector<int>> adj_list_t(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj_list[u - 1].push_back(v - 1);
        adj_list_t[v - 1].push_back(u - 1);
    }

    vector<int> comp = kosaraju(n, adj_list, adj_list_t);
    int max_comp = *max_element(comp.begin(), comp.end()) + 1;

    cout << max_comp << endl;
    for (int c : comp) {
        cout << c + 1 << " ";
    }
    cout << endl;

    return 0;
}