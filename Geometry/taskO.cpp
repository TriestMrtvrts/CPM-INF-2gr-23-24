#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double a, r, pi = 3.1415926;
    cin >> a >> r;
    cout << fixed << setprecision(6);
    if (2*r <= a)
        cout << pi*r*r;
    else if (r >= a/sqrt(2.0))
        cout << a*a;
    else
        cout << pi*r*r*(1-4*acos(a/2/r)/pi)+2*a*sqrt(r*r-a*a/4);
    cout << endl;

    return 0;
}