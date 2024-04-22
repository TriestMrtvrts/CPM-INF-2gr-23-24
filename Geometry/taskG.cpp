#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1E-9;

struct Point {
    double x, y;

    bool operator<(const Point& p) const {
        return x < p.x - EPS || (abs(x - p.x) < EPS && y < p.y - EPS);
    }
};

struct Line {
    double a, b, c;

    Line() {}
    Line(Point p, Point q) {
        a = p.y - q.y;
        b = q.x - p.x;
        c = -a * p.x - b * p.y;
        normalize();
    }

    void normalize() {
        double z = sqrt(a * a + b * b);
        if (abs(z) > EPS) {
            a /= z;
            b /= z;
            c /= z;
        }
    }

    double distance(Point p) const {
        return a * p.x + b * p.y + c;
    }
};

bool between(double l, double r, double x) {
    return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
}

bool intersect1D(double a, double b, double c, double d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return max(a, c) <= min(b, d) + EPS;
}

bool intersect(Point a, Point b, Point c, Point d, Point& left, Point& right) {
    if (!intersect1D(a.x, b.x, c.x, d.x) || !intersect1D(a.y, b.y, c.y, d.y))
        return false;

    Line m(a, b);
    Line n(c, d);
    double zn = m.a * n.b - m.b * n.a;
    if (abs(zn) < EPS) {
        if (abs(m.distance(c)) > EPS || abs(n.distance(a)) > EPS)
            return false;
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);
        left = max(a, c);
        right = min(b, d);
        return true;
    } else {
        left.x = right.x = -(m.c * n.b - m.b * n.c) / zn;
        left.y = right.y = -(m.a * n.c - m.c * n.a) / zn;
        return between(a.x, b.x, left.x) && between(a.y, b.y, left.y)
            && between(c.x, d.x, left.x) && between(c.y, d.y, left.y);
    }
}

int main() {
    Point a, b, c, d;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;

    Point left, right;
    if (intersect(a, b, c, d, left, right)) {
        cout << fixed << setprecision(6);
        if (left.x == right.x && left.y == right.y) {
            cout << left.x << " " << left.y << endl;
        } else {
            cout << left.x << " " << left.y << "\n" << right.x << " " << right.y << endl;
        }
    } else {
        cout << "Empty" << endl;
    }

    return 0;
}