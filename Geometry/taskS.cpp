#include <stdio.h>
#include <math.h>

const double PI = acos(-1.0);

class Point {
 private:
    double x, y;

 public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    void ReadPoint(void) {
        scanf("%lf %lf", &x, &y);
    }

    double GetPolarAngle() {
        double res = atan2(y, x);
        if (res < 0)
            res += 2 * PI;
        return res;
    }
};

int main(void) {
    Point p;
    p.ReadPoint();
    printf("%.6lf\n", p.GetPolarAngle());
    return 0;
}