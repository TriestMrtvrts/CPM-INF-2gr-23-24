#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    long double h, l;
    cin >> h >> l;

    long double a = pow(l, 2) - pow(h, 2);
    a = a / 2;
    a = a / h;

    cout << std::setprecision(20) << a << endl;

    return 0;
}