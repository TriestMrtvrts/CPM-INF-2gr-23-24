#include <iostream>

struct Point {
    double x, y;
};

int main() {
    int N;
    std::cin >> N;

    Point a[3];
    int Sum = 0;
    int h = 0;

    for (int i = 0; i < N; ++i) {
        ++h;
        std::cin >> a[h].x >> a[h].y;

        if (h == 3) {
            if (a[h - 2].x * (a[h].y - a[h - 1].y) + a[h - 1].x * (a[h - 2].y - a[h].y) +
                a[h].x * (a[h - 1].y - a[h - 2].y) < 0) {
                ++Sum;
            }
            a[1] = a[2];
            a[2] = a[3];
            --h;
        }
    }

    std::cout << Sum << std::endl;

    return 0;
}