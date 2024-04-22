#include <iostream>

int main() {
    int x0, y0, x1, y1, x2, y2;
    std::cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2;
    if (((x0 - x1) * (y2 - y1) == (x2 - x1) * (y0 - y1)) &&
        ((x0 - x1) * (x2 - x1) >= 0) && ((y0 - y1) * (y2 - y1) >= 0)) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
    return 0;
}