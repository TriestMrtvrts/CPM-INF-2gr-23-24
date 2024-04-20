#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

struct Vector {
    double x, y;
    void create(Point p1, Point p2) {
        x = p2.x - p1.x;
        y = p2.y - p1.y;
    }
};

struct Line {
    double a, b, c;
    void create(Point p1, Point p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = p2.x * p1.y - p2.y * p1.x;
    }
};

double distanceBetweenPoints(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double distancePointToLine(Point a, Line l) {
    return abs((a.x * l.a + a.y * l.b + l.c)) / sqrt(l.a * l.a + l.b * l.b);
}

double distance(Vector v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

double dotProduct(Vector v1, Vector v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

double crossProduct(Vector v1, Vector v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

int main() {
    Point center1, center2;
    double radius1, radius2;
    cin >> center2.x >> center2.y >> radius2;
    cin >> center1.x >> center1.y;

    if (distanceBetweenPoints(center2, center1) < radius2) {
        cout << 0 << endl;
        return 0;
    }

    radius1 = sqrt(distanceBetweenPoints(center2, center1) * distanceBetweenPoints(center2, center1) - radius2 * radius2);
    Line line;
    line.a = 2 * center2.x - 2 * center1.x;
    line.b = 2 * center2.y - 2 * center1.y;
    line.c = center1.x * center1.x + center1.y * center1.y +
         radius2 * radius2 - radius1 * radius1 -
         center2.x * center2.x - center2.y * center2.y;

    Point center, p;
    p.x = 0;
    p.y = 0;
    center.x = center1.x;
    center.y = center1.y;
    double radius;
    radius = radius1;
    Line perpendicular;
    line.c += line.a * center.x + line.b * center.y;
    perpendicular.a = -line.b;
    perpendicular.b = line.a;
    perpendicular.c = 0;
    Point base;
    base.x = (line.c * perpendicular.b - line.b * perpendicular.c) / (perpendicular.a * line.b - perpendicular.b * line.a);
    base.y = (perpendicular.c * line.a - perpendicular.a * line.c) / (perpendicular.a * line.b - perpendicular.b * line.a);
    cout << fixed;
    cout.precision(9);

    if (distancePointToLine(p, line) > radius) {
        cout << 0 << endl;
    } else if (distancePointToLine(p, line) == radius) {
        cout << 1 << endl;
        cout << base.x + center.x << " " << base.y + center.y << endl;
    } else {
        cout << 2 << endl;
        double d = sqrt(radius * radius - distancePointToLine(p, line) * distancePointToLine(p, line));
        Vector pl;
        pl.x = -line.b;
        pl.y = line.a;
        double sz = distance(pl);
        pl.x /= sz;
        pl.y /= sz;
        pl.x *= d;
        pl.y *= d;
        cout << base.x + center.x << " " << base.y + center.y << endl;
        cout << distancePointToLine(p, line) << " " << d << endl;
        cout << base.x - pl.x + center.x << " " << base.y - pl.y + center.y << endl;
        cout << base.x + pl.x + center.x << " " << base.y + pl.y + center.y << endl;
    }
    return 0;
}