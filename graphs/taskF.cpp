#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

ll bin_pow(ll n, ll k) {
  if (k == 0)
    return 1;
  if (k % 2 == 1) {
    ll x = bin_pow(n, k - 1);
    return (x * n);
  } else {
    ll x = bin_pow(n, k / 2);
    return (x * x);
  }
}

vector<ll> colors, predecessors;
vector<vector<ll>> graph;

void dfs(ll v) {
  colors[v] = 1;
  for (auto c : graph[v]) {
    if (colors[c] == 0) {
      predecessors[c] = v;
      dfs(c);
    }
    if (colors[c] == 1) {
      vector<ll> cycle;
      ll x = c;
      cycle.push_back(c);
      while (v != x) {
        cycle.push_back(v);
        v = predecessors[v];
      }
      reverse(cycle.begin(), cycle.end());
      cout << cycle.size() << endl;
      for (auto c : cycle)
        cout << c + 1 << " ";
      exit(0);
    }
  }
  colors[v] = 2;
}

void solve() {
  ll n, m;
  cin >> n >> m;
  predecessors.resize(n);
  graph.resize(n);
  colors.resize(n);
  for (ll i = 0; i < m; i++) {
    ll a, b;
    cin >> a >> b;
    a--; b--;
    graph[a].push_back(b);
  }
  for (ll i = 0; i < n; i++) {
    if (colors[i] == 0)
      predecessors[i] = i, dfs(i);
  }
  cout << -1;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0); int t = 1;
  while (t--) {
    solve();
  }
  return 0;
}