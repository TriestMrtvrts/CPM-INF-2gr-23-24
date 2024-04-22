#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    // Ввод координат точки и коэффициентов уравнения прямой
    double x, y, A, B, C;
    cin >> x >> y >> A >> B >> C;

    // Расстояние от точки до прямой
    double distance = abs(A * x + B * y + C) / sqrt(A * A + B * B);

    // Вывод расстояния с точностью не менее 10^(-6)
    cout << fixed << setprecision(6) << distance << endl;

    return 0;
}