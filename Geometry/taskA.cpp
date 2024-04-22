#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y;
};

long long distSquared(Point& p1, Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

int main() {
    int N;
    cin >> N;

    vector<Point> points(N);
    for (int i = 0; i < N; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    long long maxDistSquared = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            maxDistSquared = max(maxDistSquared, distSquared(points[i], points[j]));
        }
    }

    cout.precision(20);
    cout << fixed << sqrt(static_cast<double>(maxDistSquared)) << endl;

    return 0;
}