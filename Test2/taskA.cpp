#include <iostream>

using namespace std;

int main() {
    long long firstValue, secondValue;
    cin >> firstValue >> secondValue;

    long long operations;
    cin >> operations;

    long long result = 0;
    long long difference = abs(firstValue - secondValue);

    if (difference >= 2 * operations) {
        cout << "0 0";
        return 0;
    }

    if (difference % 2 == 1) {
        cout << "0 0";
        return 0;
    } else {
        operations -= difference / 2;
        result = -operations;
    }

    if (result > 0)
        cout << 1 << " " << result;
    else if (result == 0)
        cout << "0 0";
    else
        cout << 2 << " " << -result;

    return 0;
}