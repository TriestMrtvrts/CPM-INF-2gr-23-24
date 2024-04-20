#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

long long getSign(long long a) {
    if (a == 0)
        return 0;
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

    long long lengthSquared() {
        return x * x + y * y;
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

bool pointOnSegment(Point p, Point a, Point b) {
    Point ab = b - a;
    Point ap = p - a;
    Point bp = p - b;
    return ab % ap == 0 && ap * bp <= 0;
}

vector<Point> convexHull(vector<Point> &points) {
    long long n = points.size();
    long long minX = 1e10, minY = 1e10;
    for (long long i = 0; i < n; i++) {
        Point p = points[i];
        if (p.x < minX || p.x == minX && p.y < minY) {
            minX = p.x;
            minY = p.y;
        }
    }
    Point P(minX, minY);
    sort(points.begin(), points.end(), [P](Point a, Point b) {
        Point pa = a - P;
        Point pb = b - P;
        return pb % pa > 0 || pb % pa == 0 && pa.lengthSquared() < pb.lengthSquared();
    });
    vector<Point> res;
    res.push_back(P);
    for (long long i = 1; i < n; i++) {
        Point p = points[i];
        while (res.size() > 1) {
            Point a = res[res.size() - 2];
            Point b = res[res.size() - 1];
            Point ap = p - a;
            Point ab = b - a;
            if (ab % ap >= 0)
                res.pop_back();
            else
                break;
        }
        res.push_back(p);
    }
    return res;
}

bool pointInPolygon(Point p, vector<Point> &points) {
    long long n = points.size();
    for (long long i = 0; i < n; i++) {
        Point a = points[i];
        Point b = points[(i + 1) % n];
        if (pointOnSegment(p, a, b)) return false;
    }
    Point o = points[0];
    Point pl = points[1];
    Point pr = points[n - 1];
    if (!pointInAngle(p, o, pl, pr)) return false;
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
    Point p;
    cin >> p;
    vector<Point> points(n);
    for (auto &i : points) cin >> i;
    if (n < 3) {
        cout << "YES";
        return 0;
    }
    vector<Point> hull = convexHull(points);
    cout << (pointInPolygon(p, hull) ? "NO" : "YES");
}