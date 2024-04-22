#include <bits/stdc++.h>

using namespace std;

double calculateAngle(double x1, double y1, double x2, double y2) {
    if ((sqrt(x1 * x1 + y1 * y1) * sqrt(x2 * x2 + y2 * y2)) == 0) {
        return 0;
    } else {
        return acos((x1 * x2 + y1 * y2)/(sqrt(x1 * x1 + y1 * y1) * sqrt(x2 * x2 + y2 * y2)));
    }
}

int main() {
    double x1, y1, xo, yo, x2, y2, xp, yp;
    cin >> x1 >> y1 >> xo >> yo >> x2 >> y2 >> xp >> yp;
    double angle_u = calculateAngle(x1 - xo, y1 - yo, x2 - xo, y2 - yo);
    double angle_a = calculateAngle(x1 - xo, y1 - yo, xp - xo, yp - yo);
    double angle_b = calculateAngle(xp - xo, yp - yo, x2 - xo, y2 - yo);
    if (angle_a <= angle_u && angle_b <= angle_u && (angle_a + angle_b) <= M_PI) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}