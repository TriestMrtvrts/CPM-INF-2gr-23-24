#ifdef ONLINE_JUDGE
#pragma GCC optimize("Ofast")
#pragma GCC targer("avx2")
#endif

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

pair<ll, ll> operator+(pair<ll, ll> a, pair<ll, ll> b) {
    pair<ll, ll> res;
    res.first = min(a.first, b.first);
    if (a.first == res.first)
        res.second += a.second;
    if (b.first == res.first)
        res.second += b.second;
    return res;
}

struct SegmentTree {
    struct Node {
        Node *left, *right;
        ll upd, cnt, mn;

        Node(ll _l, ll _r) {
            upd = mn = 0;
            cnt = _r - _l;
            left = right = nullptr;
        }
    };

    Node *tree = nullptr;
    ll l, r;

    SegmentTree(ll _l, ll _r) {
        l = _l, r = _r;
        tree = new Node(l, r);
    }

    static void calc(ll l, ll r, Node *t) {
        if (t->left != nullptr && t->right != nullptr)
            return;
        ll mid = (l + r) / 2;
        if (t->left == nullptr)
            t->left = new Node(l, mid);
        if (t->right == nullptr)
            t->right = new Node(mid, r);
    }

    static void merge(Node *t) {
        t->mn = min(t->left->mn, t->right->mn);
        t->cnt = 0;
        if (t->left->mn == t->mn)
            t->cnt += t->left->cnt;
        if (t->right->mn == t->mn)
            t->cnt += t->right->cnt;
    }

    static void rec(Node *t, ll val) {
        t->mn += val;
        t->upd += val;
    }

    static void push(ll l, ll r, Node *t) {
        calc(l, r, t);
        rec(t->left, t->upd);
        rec(t->right, t->upd);
        t->upd = 0;
    }

    void add(ll lf, ll rg, ll ql, ll qr, ll val, Node *t) {
        if (lf >= qr || rg <= ql)
            return;
        if (lf >= ql && rg <= qr) {
            rec(t, val);
            return;
        }
        push(lf, rg, t);
        ll mid = (lf + rg) / 2;
        add(lf, mid, ql, qr, val, t->left);
        add(mid, rg, ql, qr, val, t->right);
        merge(t);
    }

    pair<ll, ll> get(ll lf, ll rg, ll ql, ll qr, Node *t) {
        if (lf >= qr || rg <= ql)
            return make_pair(1e9, 0);
        if (lf >= ql && rg <= qr)
            return make_pair(t->mn, t->cnt);
        push(lf, rg, t);
        ll mid = (l + r) / 2;
        return get(lf, mid, ql, qr, t->left) + get(mid, rg, ql, qr, t->right);
    }

    ll Get() {
        return (r - l) - get(l, r, l, r, tree).second;
    }

    void Add(ll _l, ll _r, ll val) {
        add(l, r, _l, _r, val, tree);
    }
};

void Fast() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
}

signed main() {
    Fast();
    ll n;
    cin >> n;
    vector<tuple<ll, ll, ll, ll>> vec;
    ll last = 2e9 + 100;
    for (ll i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        y1 += 1e9, y2 += 1e9;
        if (y1 == y2 || x1 == x2) continue;
        vec.emplace_back(x1, -1, y1, y2);
        vec.emplace_back(x2, 1, y1, y2);
        last = min(last, x1);
    }
    sort(vec.begin(), vec.end());
    SegmentTree SegT(0, 2e9 + 100);
    ll ans = 0;
    for (auto [x, type, l, r] : vec) {
        ans += (x - last) * SegT.Get();
        SegT.Add(l, r, -type);
        last = x;
    }
    cout << ans;
}