#include <iostream>
#include <cmath>
#include <iomanip>

double sideLength(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void findIncenter(double x1, double y1, double x2, double y2, double x3, double y3, double &ix, double &iy) {
    double a = sideLength(x2, y2, x3, y3);
    double b = sideLength(x1, y1, x3, y3);
    double c = sideLength(x1, y1, x2, y2);
    double perimeter = a + b + c;
    ix = (a * x1 + b * x2 + c * x3) / perimeter;
    iy = (a * y1 + b * y2 + c * y3) / perimeter;
}

int main() {
    double x1, y1, x2, y2, x3, y3;
    std::cin >> x1 >> y1;
    std::cin >> x2 >> y2;
    std::cin >> x3 >> y3;

    double ix, iy;
    findIncenter(x1, y1, x2, y2, x3, y3, ix, iy);

    std::cout << std::fixed << std::setprecision(6) << ix << " " << iy;
    return 0;
}