#include <iostream>

using namespace std;

int main() {
    double x, y, A, B, C;
    cin >> x >> y >> A >> B >> C;
    if (A * x + B * y + C == 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}