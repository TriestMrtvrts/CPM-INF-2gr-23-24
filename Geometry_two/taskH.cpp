#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <climits>

struct Point {
    int x, y;

    Point() : x(0), y(0) {}
    Point(int coordX, int coordY) : x(coordX), y(coordY) {}

    double length() const {
        return sqrt(x * x + y * y);
    }

    int squaredLength() const {
        return x * x + y * y;
    }
};

std::istream& readPoint(std::istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

std::ostream& writePoint(std::ostream& out, const Point& p) {
    out << p.x << " " << p.y;
    return out;
}

Point subtractPoints(const Point& a, const Point& b) {
    return Point(a.x - b.x, a.y - b.y);
}

int dotProduct(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

int crossProduct(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

std::vector<Point> computeConvexHull(std::vector<Point>& points) {
    Point base(INT_MAX, INT_MAX);
    for (const auto& pt : points) {
        if (pt.x < base.x || (pt.x == base.x && pt.y < base.y)) {
            base = pt;
        }
    }

    std::sort(points.begin(), points.end(), [base](const Point& a, const Point& b) {
        Point deltaA = subtractPoints(a, base);
        Point deltaB = subtractPoints(b, base);
        int cp = crossProduct(deltaB, deltaA);
        if (cp == 0) return deltaA.squaredLength() < deltaB.squaredLength();
        return cp > 0;
    });

    std::vector<Point> hull;
    for (const auto& pt : points) {
        while (hull.size() > 1 && crossProduct(subtractPoints(hull.back(), hull[hull.size() - 2]), subtractPoints(pt, hull.back())) >= 0) {
            hull.pop_back();
        }
        hull.push_back(pt);
    }
    return hull;
}

void initializeIO() {
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

int main() {
    initializeIO();
    int numPoints;
    double radius;
    std::cin >> numPoints >> radius;
    std::vector<Point> points(numPoints);
    for (auto& pt : points) readPoint(std::cin, pt);

    auto hull = computeConvexHull(points);
    double perimeter = 0;
    for (size_t i = 0; i < hull.size(); i++) {
        perimeter += subtractPoints(hull[i], hull[(i + 1) % hull.size()]).length();
    }
    perimeter += 2 * M_PI * radius;

    std::cout << std::fixed << std::setprecision(6) << perimeter;
}