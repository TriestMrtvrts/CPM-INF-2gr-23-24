#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

struct Point {
    double x, y;
};

double distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void intersectionPoints(Point c1, Point c2, double r1, double r2) {
    double d = distance(c1, c2);
    if (d > r1 + r2 || d < abs(r1 - r2)) {
        cout << "0" << endl;
        return;
    }
    if (d < 1e-6 && abs(r1 - r2) < 1e-6) {
        cout << "3" << endl;
        return;
    }
    double a = (pow(r1, 2) - pow(r2, 2) + pow(d, 2)) / (2 * d);
    double h = sqrt(pow(r1, 2) - pow(a, 2));
    double x3 = c1.x + a * (c2.x - c1.x) / d;
    double y3 = c1.y + a * (c2.y - c1.y) / d;
    Point p1 = {x3 + h * (c2.y - c1.y) / d, y3 - h * (c2.x - c1.x) / d};
    Point p2 = {x3 - h * (c2.y - c1.y) / d, y3 + h * (c2.x - c1.x) / d};
    double xH = c1.x + a * (c2.x - c1.x) / d;
    double yH = c1.y + a * (c2.y - c1.y) / d;
    double O1H = distance(c1, {xH, yH});
    double HP = distance({xH, yH}, p1);
    if (distance(p1, p2) < 1e-6) {
        cout << "1" << endl;
        cout << fixed << setprecision(10) << p1.x << " " << p1.y << endl;
    } else {
        cout << "2" << endl;
        cout << fixed << setprecision(10) << xH << " " << yH << endl;
        cout << fixed << setprecision(10) << O1H << " " << HP << endl;
        cout << fixed << setprecision(10) << p1.x << " " << p1.y << endl;
        cout << fixed << setprecision(10) << p2.x << " " << p2.y << endl;
    }
}

int main() {
    int num_tests;
    cin >> num_tests;
    for (int i = 0; i < num_tests; ++i) {
        int x1, y1, x2, y2, r1, r2;
        cin >> x1 >> y1 >> r1;
        cin >> x2 >> y2 >> r2;
        Point center1 = {x1, y1};
        Point center2 = {x2, y2};
        intersectionPoints(center1, center2, r1, r2);
    }
    return 0;
}