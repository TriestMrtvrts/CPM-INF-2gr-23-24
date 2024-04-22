#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const long double PI = acos(-1), EPS = 1e-7;

bool isEqual(long double a, long double b) {
    return abs(a - b) <= EPS;
}

long long sign(long long a) {
    if (a == 0) return 0;
    return (a > 0 ? 1 : -1);
}

struct Point {
    long double x, y;

    Point() {
        x = 0;
        y = 0;
    }

    Point(long double _x, long double _y) {
        x = _x;
        y = _y;
    }

    long long lengthSquared() {
        return x * x + y * y;
    }

    long double length() {
        return sqrt(lengthSquared());
    }
};

bool operator==(Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

Point operator-(Point a, Point b) {
    return Point(a.x - b.x, a.y - b.y);
}

Point operator+(Point a, Point b) {
    return Point(a.x + b.x, a.y + b.y);
}

Point operator*(Point a, long long k) {
    return Point(a.x * k, a.y * k);
}

Point operator*(long long k, Point a) {
    return a * k;
}

void operator-=(Point &a, Point b) {
    a = a - b;
}

void operator+=(Point &a, Point b) {
    a = a + b;
}

void operator*=(Point &a, long long k) {
    a = a * k;
}

long long operator*(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

long long operator%(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

long double getAngle(Point a, Point b, Point c) {
    Point ab = b - a;
    Point cb = b - c;
    long long res = atan2(ab % cb, ab * cb);
    return abs(res);
}

istream &operator>>(istream &in, Point &p) {
    in >> p.x >> p.y;
    return in;
}

ostream &operator<<(ostream &out, Point p) {
    out << p.x << " " << p.y;
    return out;
}

struct Line {
    long double a, b, c;

    Line(Point p1, Point p2) {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = p1.x * p2.y - p2.x * p1.y;
        if (isEqual(a, 0) && isEqual(b, 0)) {
            a = 1;
        }
    }

    Line(long double _a, long double _b, long double _c) {
        a = _a;
        b = _b;
        c = _c;
        if (isEqual(a, 0) && isEqual(b, 0)) {
            a = 1;
        }
    }

    long double distanceToPoint(Point p) {
        return ((long double) abs(a * p.x + b * p.y + c)) / (sqrt(a * a + b * b));
    }

    long double valueAtPoint(Point p) {
        return p.x * a + p.y * b + c;
    }

    Point intersectLines(Line l) {
        return Point((long double) (b * l.c - c * l.b) / (long double) (a * l.b - b * l.a),
                     (long double) (c * l.a - a * l.c) / (long double) (a * l.b - b * l.a));
    }
};

void setupIO() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
}

signed main() {
    setupIO();
    Point p1, p2;
    cin >> p1 >> p2;
    long double k, t;
    cin >> k >> t;
    if ((k * p1.x + t - p1.y) * (k * p2.x + t - p2.y) < 0) {
        cout << "No solution.";
        return 0;
    }
    Line l(k, -1, t);
    Line ll(1, k, l.b * p1.x - l.a * p1.y);
    Point p = l.intersectLines(ll);
    Point pp = 2 * p - p1;
    Line L(pp, p2);
    cout << fixed << setprecision(3);
    Point ppp = L.intersectLines(l);
    cout << (p1 - ppp).length() + (ppp - p2).length();
}