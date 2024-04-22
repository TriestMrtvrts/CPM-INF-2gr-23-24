#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

const long double PI = acos(-1.0);

struct Vector2D {
    long long x, y;

    Vector2D(long long x = 0, long long y = 0) : x(x), y(y) {}

    Vector2D operator-(const Vector2D& other) const {
        return {x - other.x, y - other.y};
    }

    long long dot(const Vector2D& other) const {
        return x * other.x + y * other.y;
    }

    long long cross(const Vector2D& other) const {
        return x * other.y - y * other.x;
    }

    long double magnitude() const {
        return sqrt(x * x + y * y);
    }
};

long double computeAngle(const Vector2D& a, const Vector2D& b, const Vector2D& c) {
    Vector2D ba = a - b;
    Vector2D bc = c - b;
    return abs(atan2(ba.cross(bc), ba.dot(bc)));
}

void setupIO() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
}

int main() {
    setupIO();
    Vector2D p1, p2, p3;
    cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
    cout << fixed << setprecision(20);
    long double angle1 = computeAngle(p1, p2, p3);
    long double angle2 = computeAngle(p2, p3, p1);
    long double angle3 = computeAngle(p3, p1, p2);
    cout << max({angle1, angle2, angle3}) * 180 / PI;
}