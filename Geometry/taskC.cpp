#include <bits/stdc++.h>

using namespace std;

struct Vector {
    double x, y;
};
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
    Vector v1, v2, v3;
    double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    v1.x = x2 - x1;
    v1.y = y2 - y1;
    cin >> x1 >> y1 >> x2 >> y2;
    v2.x = x2 - x1;
    v2.y = y2 - y1;
    v3.x = 1;
    v3.y = 0;
    cout << fixed << setprecision(7);
    cout << distance(v1) << " " << distance(v2) << "\n";
    cout << v1.x + v2.x << " " << v1.y + v2.y << "\n";
    cout << dotProduct(v1, v2) << " " << crossProduct(v1, v2) << "\n";
    cout << abs(crossProduct(v1, v2)) / 2 << "\n";
    double a = atan2(crossProduct(v3, v1) / distance(v1) / distance(v3), dotProduct(v3, v1) / distance(v1) / distance(v3));
    double b = atan2(crossProduct(v3, v2) / distance(v2) / distance(v3), dotProduct(v3, v2) / distance(v2) / distance(v3));
    double c = atan2(crossProduct(v1, v2) / distance(v2) / distance(v1), dotProduct(v1, v2) / distance(v2) / distance(v1));
    if (a < 0) {
        cout << 2 * M_PI + a << " ";
    } else {
        cout << a << " ";
    }
    if (b < 0) {
        cout << 2 * M_PI + b << "\n";
    } else {
        cout << b << "\n";
    }
    if (c < 0) {
        cout << 2 * M_PI + c << "\n";
        cout << (2 * M_PI + c) / (2 * M_PI);
    } else {
        cout << c << "\n";
        cout << c / (2 * M_PI);
    }
}