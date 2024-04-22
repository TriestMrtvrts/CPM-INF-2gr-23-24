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

const long double pi = acos(-1), eps = 1e-7;

bool isEqual(long double a, long double b) {
    return abs(a - b) <= eps;
}

long long signInt(long long a) {
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

long double calculateAngle(Point a, Point b, Point c) {
    Point ab = b - a;
    Point cb = b - c;
    long double result = atan2(abs(ab % cb), abs(ab * cb));
    if (result < 0) {
        result += 2 * pi;
    }
    return result;
}

long double convertToDegrees(long double angleInRadians) {
    return angleInRadians * 90 / pi;
}

istream &operator>>(istream &in, Point &p) {
    in >> p.x >> p.y;
    return in;
}

ostream &operator<<(ostream &out, Point p) {
    out << p.x << " " << p.y;
    return out;
}

bool isPointOnSegment(Point p, Point a, Point b) {
    Point ap = p - a;
    Point ab = b - a;
    Point bp = p - b;
    Point ba = a - b;
    return (ap % ab == 0 && signInt(ap * ab) >= 0 && signInt(bp * ba) >= 0);
}

bool checkSegment(Point p, Point a, Point b) {
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

    long long valueAtPoint(Point p) {
        return p.x * a + p.y * b + c;
    }

    Point intersectLines(Line l) {
        return Point((long double) (b * l.c - c * l.b) / (long double) (a * l.b - b * l.a),
                     (long double) (c * l.a - a * l.c) / (long double) (a * l.b - b * l.a));
    }
};

bool checkRay(Point p, Point a, Point b) {
    Point ab = b - a;
    Point ap = p - a;
    return (ab * ap >= 0);
}

bool areCollinear(Point a, Point b, Point c, Point d) {
    Line l1(a, b);
    Line l2(c, d);
    return l1.a * l2.b - l2.a * l1.b == 0;
}

bool isSegmentOnLine(Point a, Point b, Point c, Point d) {
    Point ca = a - c;
    Point cb = b - c;
    Point cd = d - c;
    Point da = a - d;
    Point db = b - d;
    Point dc = c - d;
    return signInt(cd % ca) * signInt(cd % cb) <= 0 || signInt(dc % da) * signInt(dc % db) <= 0;
}

long double calculateLengthOne(Point A, Point B, Point C, Point D) { // A -> C
    return (A - C).length();
}

long double calculateLengthTwo(Point A, Point B, Point C, Point D) { // A -> CD (segment)
    if (checkSegment(A, C, D)) {
        return Line(C, D).distanceToPoint(A);
    } else {
        return min((A - C).length(), (A - D).length());
    }
}

long double calculateLengthThree(Point A, Point B, Point C, Point D) { // A -> CD (Beam)
    if (checkRay(A, C, D)) {
        return Line(C, D).distanceToPoint(A);
    } else {
        return (A - C).length();
    }
}

long double calculateLengthFour(Point A, Point B, Point C, Point D) { // A -> CD (line)
    return Line(C, D).distanceToPoint(A);
}

long double calculateLengthEight(Point A, Point B, Point C, Point D) { // AB (segment) -> CD (line)
    if (isSegmentOnLine(A, B, C, D)) {
        return 0;
    }
    return min(calculateLengthFour(A, B, C, D), calculateLengthFour(B, A, C, D));
}

bool checkTwoSegments(Point a, Point b, Point c, Point d) {
    if (areCollinear(a, b, c, d)) {
        return min({calculateLengthTwo(a, b, c, d), calculateLengthTwo(b, a, c, d),
                    calculateLengthTwo(c, d, a, b), calculateLengthTwo(d, c, a, b)}) == 0;
    }
    return (calculateLengthEight(a, b, c, d) == 0 && calculateLengthEight(c, d, a, b) == 0);
}

long double calculateLengthFive(Point A, Point B, Point C, Point D) { // AB (segment) -> C
    return calculateLengthTwo(C, D, A, B);
}

long double calculateLengthSix(Point A, Point B, Point C, Point D) { // AB (segment) -> CD (segment)
    if (checkTwoSegments(A, B, C, D)) {
        return 0;
    } else {
        return min({calculateLengthTwo(A, B, C, D), calculateLengthTwo(B, A, C, D),
                    calculateLengthTwo(C, D, A, B), calculateLengthTwo(D, C, A, B)});
    }
}

long double calculateLengthNine(Point A, Point B, Point C, Point D) { // AB (beam) -> C
    return calculateLengthThree(C, D, A, B);
}

long double calculateLengthTwelve(Point A, Point B, Point C, Point D) { // AB (beam) -> CD (line)
    if (areCollinear(A, B, C, D)) {
        if (Line(C, D).distanceToPoint(A) == 0) {
            return 0;
        }
        return Line(C, D).distanceToPoint(A);
    }
    if (signInt((C - A) % (C - D)) * signInt((C - B) % (C - D)) <= 0 &&
        signInt((D - A) % (D - C)) * signInt((D - B) % (D - C)) <= 0) {
        return 0;
    }
    if (calculateLengthFour(A, B, C, D) < calculateLengthFour(B, A, C, D)) {
        return calculateLengthFour(A, B, C, D);
    }
    return 0;
}

long double calculateLengthEleven(Point A, Point B, Point C, Point D) { // AB (beam) -> CD (beam)
    if (areCollinear(A, B, C, D)) {
        return min({calculateLengthThree(A, B, C, D), calculateLengthThree(B, A, C, D),
                    calculateLengthThree(C, D, A, B), calculateLengthThree(D, C, A, B)});
    }
    if (calculateLengthTwelve(A, B, C, D) == 0 && calculateLengthTwelve(C, D, A, B) == 0) {
        return 0;
    }
    return min({calculateLengthThree(A, B, C, D), calculateLengthThree(B, A, C, D),
                calculateLengthThree(C, D, A, B), calculateLengthThree(D, C, A, B)});
}

bool isSegmentOnBeam(Point a, Point b, Point c, Point d) {
    if (areCollinear(a, b, c, d)) {
        if (Line(c, d).distanceToPoint(a) == 0) {
            return min(calculateLengthThree(a, b, c, d), calculateLengthThree(b, a, c, d)) == 0;
        } else {
            return false;
        }
    }
    if (calculateLengthEight(a, b, c, d) == 0 && calculateLengthTwelve(c, d, a, b) == 0) {
        return true;
    }
    return false;
}

long double calculateLengthSeven(Point A, Point B, Point C, Point D) { // AB (segment) -> CD (beam)
    if (isSegmentOnBeam(A, B, C, D)) {
        return 0;
    }
    return min({calculateLengthThree(A, B, C, D), calculateLengthThree(B, A, C, D), calculateLengthTwo(C, D, A, B)});
}

long double calculateLengthTen(Point A, Point B, Point C, Point D) { // AB (beam) -> CD (segment)
    return calculateLengthSeven(C, D, A, B);
}

long double calculateLengthThirteen(Point A, Point B, Point C, Point D) { // AB (line) -> C
    return calculateLengthFour(C, D, A, B);
}

long double calculateLengthFourteen(Point A, Point B, Point C, Point D) { // AB (line) -> CD (segment)
    return calculateLengthEight(C, D, A, B);
}

long double calculateLengthFifteen(Point A, Point B, Point C, Point D) {  // AB (line) -> CD (beam)
    return calculateLengthTwelve(C, D, A, B);
}

long double calculateLengthSixteen(Point A, Point B, Point C, Point D) { // AB (line) -> CD (line)
    if (areCollinear(A, B, C, D)) {
        return calculateLengthFour(A, B, C, D);
    }
    return 0;
}

void setupIO() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
}

signed main() {
    setupIO();
    Point A, B, C, D;
    cin >> A >> B >> C >> D;
    cout << fixed << setprecision(20);
    cout << calculateLengthOne(A, B, C, D) << endl;
    cout << calculateLengthTwo(A, B, C, D) << endl;
    cout << calculateLengthThree(A, B, C, D) << endl;
    cout << calculateLengthFour(A, B, C, D) << endl;
    cout << calculateLengthFive(A, B, C, D) << endl;
    cout << calculateLengthSix(A, B, C, D) << endl;
    cout << calculateLengthSeven(A, B, C, D) << endl;
    cout << calculateLengthEight(A, B, C, D) << endl;
    cout << calculateLengthNine(A, B, C, D) << endl;
    cout << calculateLengthTen(A, B, C, D) << endl;
    cout << calculateLengthEleven(A, B, C, D) << endl;
    cout << calculateLengthTwelve(A, B, C, D) << endl;
    cout << calculateLengthThirteen(A, B, C, D) << endl;
    cout << calculateLengthFourteen(A, B, C, D) << endl;
    cout << calculateLengthFifteen(A, B, C, D) << endl;
    cout << calculateLengthSixteen(A, B, C, D) << endl;
}