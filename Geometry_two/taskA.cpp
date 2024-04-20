#include <iostream>
#include <cmath>
#include <vector>

std::pair<int, std::vector<std::pair<double, double>>> circle_line_intersection(
    double x0, double y0, double r, double A, double B, double C) {

    double numerator = std::abs(A * x0 + B * y0 + C);
    double denominator = std::sqrt(A * A + B * B);
    double d = numerator / denominator;
    std::vector<std::pair<double, double>> points;

    if (d > r) {
        return std::make_pair(0, points);
    } else if (d == r) {
        double xp = x0 - A * (A * x0 + B * y0 + C) / (A * A + B * B);
        double yp = y0 - B * (A * x0 + B * y0 + C) / (A * A + B * B);
        points.push_back(std::make_pair(xp, yp));
        return std::make_pair(1, points);
    } else {
        double len = std::sqrt(r * r - d * d) / denominator;
        double dir_x = -B;
        double dir_y = A;
        double xp = x0 - A * (A * x0 + B * y0 + C) / (A * A + B * B);
        double yp = y0 - B * (A * x0 + B * y0 + C) / (A * A + B * B);
        double x1 = xp + dir_x * len;
        double y1 = yp + dir_y * len;
        double x2 = xp - dir_x * len;
        double y2 = yp - dir_y * len;
        points.push_back(std::make_pair(x1, y1));
        points.push_back(std::make_pair(x2, y2));
        return std::make_pair(2, points);
    }
}

int main() {
    double x0, y0, r, A, B, C;
    std::cin >> x0 >> y0 >> r >> A >> B >> C;

    std::pair<int, std::vector<std::pair<double, double>>> result = circle_line_intersection(x0, y0, r, A, B, C);
    std::cout << result.first << std::endl;
    for (const auto& point : result.second) {
        std::cout << point.first << " " << point.second << std::endl;
    }

    return 0;
}