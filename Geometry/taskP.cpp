#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <map>
#include <string>
#include <stack>
#include <queue>

using namespace std;

const long double pi = acos(-1), epsilon = 1e-7;

bool isEqual(long double a, long double b) {
    return abs(a - b) <= epsilon;
}

long long sign(long long a) {
    if (a == 0) return 0;
    return (a > 0 ? 1 : -1);
}

struct Point {
    long long x, y;

    Point() {
        x = 0;
        y = 0;
    }

    Point(long long _x, long long _y) {
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

bool operator ==(Point a, Point b) {
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
    long double result = atan2(ab % cb, ab * cb);
//    if (result < 0) {
//        result += 2 * pi;
//    }
    return abs(result);
}

istream &operator>>(istream &in, Point &p) {
    in >> p.x >> p.y;
    return in;
}

ostream &operator<<(ostream &out, Point p) {
    out << p.x << " " << p.y;
    return out;
}

bool isOnSegment(Point p, Point a, Point b) {
    Point ap = p - a;
    Point ab = b - a;
    Point bp = p - b;
    Point ba = a - b;
    return (ab * ap >= 0 && bp * ba >= 0);
}

struct Line {
    long long a, b, c;

    Line(Point p1, Point p2) {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = p1.x * p2.y - p2.x * p1.y;
        if (a == 0 && b == 0) {
            a = 1;
        }
    }

    Line(long long _a, long long _b, long long _c) {
        a = _a;
        b = _b;
        c = _c;
        if (a == 0 && b == 0) {
            a = 1;
        }
    }

    long double distanceToPoint(Point p) {
        return ((long double) abs(a * p.x + b * p.y + c)) / (sqrt(a * a + b * b));
    }

    long long evaluate(Point p) {
        return p.x * a + p.y * b + c;
    }

    Point intersect(Line l) {
        return Point((long double) (b * l.c - c * l.b) / (long double) (a * l.b - b * l.a),
                     (long double) (c * l.a - a * l.c) / (long double) (a * l.b - b * l.a));
    }
};

long double distanceBetweenTwoPoints(Point A, Point B, Point C, Point D) { // A -> CD (segment)
    if (isOnSegment(A, C, D)) {
        if (C == D) {
            return (A - C).length();
        }
        return Line(C, D).distanceToPoint(A);
    } else {
        return min((A - C).length(), (A - D).length());
    }
}

void setupIO() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
}

signed main() {
    setupIO();
    Point A, B, C;
    long double L;
    cin >> A >> B >> C >> L;
    cout << fixed << setprecision(20);
    Point D;
    cout << max(distanceBetweenTwoPoints(C, D, A, B) - L, (long double) 0) << endl
         << max(max((C - B).length(), (C - A).length()) - L, (long double) 0);
}