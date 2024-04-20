#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

long long getSign(long long a) {
    if (a == 0) return 0;
    return (a < 0 ? -1 : 1);
}

struct Point {
    long long x, y;

    Point() {
        x = y = 0;
    }

    Point(long long _x, long long _y) {
        x = _x;
        y = _y;
    }

    long double length() {
        return sqrt(x * x + y * y);
    }
};

istream &operator>>(istream &in, Point &p) {
    in >> p.x >> p.y;
    return in;
}

ostream &operator<<(ostream &out, Point &p) {
    out << p.x << " " << p.y;
    return out;
}

Point operator-(Point a, Point b) {
    return Point(a.x - b.x, a.y - b.y);
}

long long operator*(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

long long operator%(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

bool pointInAngle(Point p, Point o, Point a, Point b) {
    Point op = p - o;
    Point oa = a - o;
    Point ob = b - o;
    return getSign(op % oa) * getSign(op % ob) <= 0;
}

bool pointInTriangle(Point p, Point a, Point b, Point c) {
    return pointInAngle(p, a, b, c) && pointInAngle(p, b, c, a) && pointInAngle(p, c, a, b);
}

vector<Point> convexHull(vector<Point> &points) {
    long long minX = 1e10, minY = 1e10;
    long long n = points.size();
    for (long long i = 0; i < n; i++) {
        if (points[i].x < minX) {
            minX = points[i].x;
            minY = points[i].y;
        } else if (points[i].x == minX && points[i].y < minY) {
            minX = points[i].x;
            minY = points[i].y;
        }
    }
    Point p(minX, minY);
    sort(points.begin(), points.end(), [p](Point a, Point b) {
        Point pa = a - p;
        Point pb = b - p;
        return pb % pa > 0 || pb % pa == 0 && pa.length() < pb.length();
    });
    vector<Point> res;
    res.push_back(p);
    for (long long i = 1; i < n; i++) {
        Point cur = points[i];
        while (res.size() > 2) {
            Point a = res[res.size() - 2];
            Point b = res[res.size() - 2];
            Point ap = cur - a;
            Point ab = b - a;
            if (ab % ap >= 0)
                res.pop_back();
            else
                break;
        }
        res.push_back(cur);
    }
    return res;
}

long double calculateArea(vector<Point> &points) {
    long double ans = 0;
    long long n = points.size();
    Point o;
    for (long long i = 0; i < n; i++) {
        Point a = points[i];
        Point b = points[(i + 1) % n];
        Point oa = a - o;
        Point ob = b - o;
        ans += oa % ob;
    }
    ans = abs(ans);
    return ans / 2;
}

bool pointInPolygon(Point p, vector<Point> &points) {
    long long n = points.size();
    Point o = points[0];
    Point pl = points[1];
    Point pr = points[n - 1];
    if (!pointInAngle(p, o, pl, pr))
        return false;
    long long l = 1, r = n - 1;
    while (r - l > 1) {
        long long mid = (l + r) / 2;
        Point pm = points[mid];
        if (pointInAngle(p, o, pl, pm)) {
            r = mid;
            pr = pm;
        } else {
            l = mid;
            pl = pm;
        }
    }
    return pointInTriangle(p, o, pl, pr);
}

void setupIO() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
}

int main() {
    setupIO();
    long long n;
    cin >> n;
    vector<pair<long double, vector<Point>>> polygons(n + 1);
    polygons[0].first = 0;
    for (long long i = 1; i <= n; i++) {
        long long k;
        cin >> k;
        polygons[i].second.resize(k);
        for (long long j = 0; j < k; j++) {
            cin >> polygons[i].second[j];
        }
        polygons[i].first = calculateArea(polygons[i].second);
    }
    sort(polygons.begin(), polygons.end(),
         [](pair<long double, vector<Point>> &a, pair<long double, vector<Point>> &b) {
             return a.first < b.first;
         });
    vector<bool> used(n + 1, false);
    long long q;
    cin >> q;
    while (q--) {
        Point p;
        cin >> p;
        long long l = 0, r = n + 1;
        while (r - l > 1) {
            long long mid = (l + r) / 2;
            if (pointInPolygon(p, polygons[mid].second))
                r = mid;
            else
                l = mid;
        }
        if (r == n + 1)
            continue;
        used[r] = true;
    }
    long double ans = 0;
    for (long long i = 1; i <= n; i++) {
        if (used[i]) {
            ans += polygons[i].first - polygons[i - 1].first;
        }
    }
    cout << fixed << setprecision(20) << ans;
}