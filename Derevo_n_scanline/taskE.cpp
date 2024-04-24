#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <iomanip>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

using int64 = long long;

const int MAXN = 8e5 + 5;
pair<int64, long long> t[MAXN];
int64 inc[MAXN];

long long comp_delta[MAXN];

pair<int64, long long> merge(pair<int64, long long> a, pair<int64, long long> b) {
    if (a.first > b.first) {
        swap(a, b);
    }
    if (a.first == b.first) {
        return {a.first, a.second + b.second};
    }
    return a;
}

void build(int v, int64 l, int64 r) {
    if (r - l <= 0) {
        return;
    }
    if (r - l == 1) {
        t[v] = {0, comp_delta[l]};
        inc[v] = 0;
        return;
    }
    int64 m = (l + r) / 2;
    build(v * 2, l, m);
    build(v * 2 + 1, m, r);
    t[v] = merge(t[v * 2], t[v * 2 + 1]);
    inc[v] = 0;
}

void push(int v, int64 l, int64 r) {
    if (inc[v] != 0) {
        inc[v * 2] += inc[v];
        t[2 * v].first += inc[v];
        inc[v * 2 + 1] += inc[v];
        t[2 * v + 1].first += inc[v];
        inc[v] = 0;
    }
}

void add(int v, int64 l, int64 r, int64 ql, int64 qr, int64 delta) {
    if (ql <= l && r <= qr) {
        inc[v] += delta;
        t[v].first += delta;
        return;
    }
    if (qr <= l || r <= ql) {
        return;
    }
    push(v, l, r);
    int64 m = (r + l) / 2;
    add(v * 2, l, m, ql, qr, delta);
    add(v * 2 + 1, m, r, ql, qr, delta);
    t[v] = merge(t[v * 2], t[v * 2 + 1]);
}

long long zero_cnt() {
    if (t[1].first == 0) {
        return t[1].second;
    }
    return 0;
}

struct Border {
    long long y;
    long long x1, x2;
    int delta;

    bool operator<(const Border &rhs) const {
        if (y < rhs.y)
            return true;
        if (rhs.y < y)
            return false;
        if (x1 < rhs.x1)
            return true;
        if (rhs.x1 < x1)
            return false;
        if (x2 < rhs.x2)
            return true;
        if (rhs.x2 < x2)
            return false;
        return delta < rhs.delta;
    }

    bool operator>(const Border &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Border &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Border &rhs) const {
        return !(*this < rhs);
    }
};

vector<long long> x_coordinates;
vector<Border> borders;

void solve() {
    sort(x_coordinates.begin(), x_coordinates.end());
    for (size_t i = 0; i < x_coordinates.size(); ++i) {
        comp_delta[i] = x_coordinates[i + 1] - x_coordinates[i];
    }
    comp_delta[x_coordinates.size() - 1] = 0;

    map<long long, size_t> mp;
    for (size_t i = 0; i < x_coordinates.size(); ++i) {
        mp[x_coordinates[i]] = i;
    }

    build(1, 0, x_coordinates.size());
    sort(borders.begin(), borders.end());
    long long start = zero_cnt();
    long long ans = 0;
    long long last_y = 0;
    for (auto e : borders) {
        long long v = (e.y - last_y) * (start - zero_cnt());
        ans += v;
        last_y = e.y;
        add(1, 0, x_coordinates.size(), mp[e.x1], mp[e.x2], e.delta);
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int64 k, n;
    cin >> k >> n;
    int64 x = 0;
    int64 y = 0;
    for (int i = 0; i < n; ++i) {
        string direction;
        int64 distance;
        cin >> direction >> distance;
        int64 new_x = x;
        int64 new_y = y;
        if (direction == "N") {
            new_y += distance;
        } else if (direction == "S") {
            new_y -= distance;
        } else if (direction == "W") {
            new_x -= distance;
        } else if (direction == "E") {
            new_x += distance;
        }

        long long y_max = max(y + k, new_y + k);
        long long y_min = min(y, new_y);
        long long x_max = max(x + k, new_x + k);
        long long x_min = min(x, new_x);

        x_coordinates.push_back(x_max);
        x_coordinates.push_back(x_min);
        borders.push_back(Border{y_min, x_min, x_max, 1});
        borders.push_back(Border{y_max, x_min, x_max, -1});
        x = new_x;
        y = new_y;
    }
    solve();
}