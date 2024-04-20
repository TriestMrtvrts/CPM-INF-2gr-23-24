#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

const long double epsilon = 1e-8;
const long double pi_val = acos(-1);

bool is_close(long double a, long double b) {
    return abs(a - b) <= epsilon;
}

long double sign(long double a) {
    if (is_close(a, (long double) 0))
        return 0;
    return (a < 0 ? -1 : 1);
}

struct Point {
    long double x, y;

    Point() {
        x = y = 0;
    }

    Point(long double _x, long double _y) {
        x = _x;
        y = _y;
    }

    long double length() {
        return sqrt(x * x + y * y);
    }

    long double length_squared() {
        return x * x + y * y;
    }
};

Point operator+(Point a, Point b) {
    return Point(a.x + b.x, a.y + b.y);
}

Point operator-(Point a, Point b) {
    return Point(a.x - b.x, a.y - b.y);
}

long double operator*(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

long double operator%(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

istream &operator>>(istream &in, Point &p) {
    in >> p.x >> p.y;
    return in;
}

ostream &operator<<(ostream &out, Point &p) {
    out << p.x << " " << p.y;
    return out;
}

struct Line {
    long double a, b, c;

    Line() {
        a = 1;
        b = c = 0;
    }

    Line(long double _a, long double _b, long double _c) {
        a = _a;
        b = _b;
        c = _c;
    }

    Line(Point p1, Point p2) {
        if (p1.x == p2.x) {
            a = 1;
            b = 0;
            c = -p1.x;
        } else if (p1.y == p2.y) {
            a = 0;
            b = 1;
            c = -p1.y;
        } else {
            a = p1.y - p2.y;
            b = p2.x - p1.x;
            c = p1 % p2;
        }
    }

    Point intersect(Line l) const {
        long double p1 = l.b * c - l.c * b;
        long double q1 = l.a * b - l.b * a;
        long double p2 = l.a * c - l.c * a;
        long double q2 = l.b * a - l.a * b;
        return Point(p1 / q1, p2 / q2);
    }

    void output() {
        cout << a << " " << b << " " << c;
    }
};

long double calculate_area(vector<Point> &points, long double x) {
    long double area1 = 0, area2 = 0;
    int n = points.size();
    for (int i = 0; i < n; i++) {
        Point a = points[i];
        Point b = points[(i + 1) % n];
        if (a.x == x) {
            area2 += (b.x - a.x) * (a.y + b.y);
        } else if (b.x == x) {
            area1 += (b.x - a.x) * (a.y + b.y);
        } else if ((x - a.x) * (x - b.x) < 0) {
            Line l1(a, b);
            Line l2(1, 0, -x);
            Point p = l1.intersect(l2);
            if (x < b.x) {
                area1 += (p.x - a.x) * (a.y + p.y);
                area2 += (b.x - p.x) * (b.y + p.y);
            } else {
                area2 += (p.x - a.x) * (a.y + p.y);
                area1 += (b.x - p.x) * (b.y + p.y);
            }
        } else if (a.x < x) {
            area1 += (b.x - a.x) * (b.y + a.y);
        } else {
            area2 += (b.x - a.x) * (a.y + b.y);
        }
    }
    return abs(abs(area1) - abs(area2));
}

void setup_io() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
}

signed main() {
    setup_io();
    int num_points;
    cin >> num_points;
    vector<Point> points(num_points);
    for (auto &point : points) cin >> point;
    long double left = 1e10, right = -1e10;
    for (int i = 0; i < num_points; i++) {
        left = min(left, points[i].x);
        right = max(right, points[i].x);
    }
    while (right - left > epsilon) {
        long double left_mid = (2 * left + right) / 3;
        long double right_mid = (left + 2 * right) / 3;
        long double dl = calculate_area(points, left_mid);
        long double dr = calculate_area(points, right_mid);
        if (dl < dr)
            right = right_mid;
        else
            left = left_mid;
    }
    cout << fixed << setprecision(20) << left;
}