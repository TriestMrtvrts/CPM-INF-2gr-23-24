#include <iostream>
#include <iomanip>

using namespace std;

void findLineEquation(int x1, int y1, int x2, int y2, double &A, double &B, double &C) {
    A = y2 - y1;
    B = x1 - x2;
    C = x2 * y1 - x1 * y2;
}
int main() {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    double A, B, C;
    findLineEquation(x1, y1, x2, y2, A, B, C);
    cout << fixed << setprecision(6) << A << " " << B << " " << C << endl;
    return 0;
}