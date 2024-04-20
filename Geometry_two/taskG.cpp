#include <bits/stdc++.h>

using namespace std;

using ld = long double;
using ll = long long;

const int base = 101;

ll max(ll a, ll b) { return (a > b) ? a : b; }

ll bin_pow(ll n, ll k) {
  if (k == 0)
    return 1;
  if (k % 2 == 0) {
    ll x = bin_pow(n, k / 2);
    return x * x;
  } else {
    ll x = bin_pow(n, k - 1);
    return x * k;
  }
}

const ld INF = 1E200;
const ld EP = 1E-10;
const ll MAXV = 300;
const ld PI = 3.14159265;

struct Point {
  ll x;
  ll y;

  Point(ll a = 0, ll b = 0) {
    x = a;
    y = b;
  }
};

struct LineSegment {
  Point start;
  Point end;

  LineSegment(Point a, Point b) {
    start = a;
    end = b;
  }

  LineSegment() {}
};

struct Line {
  ld a;
  ld b;
  ld c;

  Line(ld d1 = 1, ld d2 = -1, ld d3 = 0) {
    a = d1;
    b = d2;
    c = d3;
  }
};

ld distance(Point p1, Point p2) {
  return (sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

bool equalPoint(Point p1, Point p2) {
  return ((abs(p1.x - p2.x) < EP) && (abs(p1.y - p2.y) < EP));
}

ll vec(Point sp, Point ep, Point op) {
  return ((sp.x - op.x) * (ep.y - op.y) - (ep.x - op.x) * (sp.y - op.y));
}

ll scalar(Point p1, Point p2, Point p0) {
  return ((p1.x - p0.x) * (p2.x - p0.x) + (p1.y - p0.y) * (p2.y - p0.y));
}

ll crossProductX(Point p1, Point p2, Point p3) {
  return ((p2.x - p1.x) * (p3.x - p1.x));
}

ll crossProductY(Point p1, Point p2, Point p3) {
  return ((p2.y - p1.y) * (p3.y - p1.y));
}

bool collinear(Point a, Point b, Point c) {
  int k, w;
  if (b.x == a.x) {
    return (c.x == a.x && c.y >= min(a.y, b.y) && a.x <= max(a.y, b.y));
  }
  k = (b.y - a.y) / (b.x - a.x);
  w = a.y - k * a.x;
  return c.y == c.x * k + w;
}
struct Pt {
  ll x, y;
};

bool cmp(Pt a, Pt b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }

bool clockwise(Pt a, Pt b, Pt c) {
  return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0;
}

bool counterClockwise(Pt a, Pt b, Pt c) {
  return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0;
}

void convexHull(vector<Pt> &points) {
  if (points.size() == 1)
    return;
  sort(points.begin(), points.end(), &cmp);
  Pt p1 = points[0], p2 = points.back();
  vector<Pt> upper, lower;
  upper.push_back(p1);
  lower.push_back(p1);
  for (size_t i = 1; i < points.size(); ++i) {
    if (i == points.size() - 1 || clockwise(p1, points[i], p2)) {
      while (upper.size() >= 2 && !clockwise(upper[upper.size() - 2], upper[upper.size() - 1], points[i]))
        upper.pop_back();
      upper.push_back(points[i]);
    }
    if (i == points.size() - 1 || counterClockwise(p1, points[i], p2)) {
      while (lower.size() >= 2 && !counterClockwise(lower[lower.size() - 2], lower[lower.size() - 1], points[i]))
        lower.pop_back();
      lower.push_back(points[i]);
    }
  }
  points.clear();
  for (size_t i = 0; i < upper.size(); ++i)
    points.push_back(upper[i]);
  for (size_t i = lower.size() - 2; i > 0; --i)
    points.push_back(lower[i]);
}
void solve() {
  ll n;
  cin >> n;
  vector<Pt> points(n);
  for (ll i = 0; i < n; i++) {
    cin >> points[i].x >> points[i].y;
  }
  convexHull(points);
  cout << points.size() << endl;
  for (ll i = 0; i < (ll)points.size(); i++) {
    cout << points[i].x << ' ' << points[i].y << endl;
  }
  ll area = 0;
  for (ll i = 2; i < (ll)points.size(); i++) {
    area += abs((points[0].x * (points[i - 1].y - points[i].y) + points[i - 1].x * (points[i].y - points[0].y) +
               points[i].x * (points[0].y - points[i - 1].y)));
  }
  ll cur = area;
  area /= 2;
  string s = to_string(area);
  if (cur % 2 == 1) {
    s += ".5";
  }
  cout << s;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  ll t = 1;
  while (t--) {
    solve();
  }
  return 0;
}