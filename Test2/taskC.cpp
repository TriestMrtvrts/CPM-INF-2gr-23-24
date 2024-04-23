#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    vector<long long> powerOfTwo;
    long long result = 1;

    // Заполнение вектора степенями двойки
    while (result < 1e18 / 2) {
        powerOfTwo.push_back(result - 1);
        result *= 2;
    }
    powerOfTwo.push_back(result - 1);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        long long x, sum = 0;
        cin >> x;

        // Вычисление минимального количества пауз
        while (x > 0) {
            int left = 0, right = powerOfTwo.size(), mid;

            // Бинарный поиск
            while (right - left > 1) {
                mid = (right + left) / 2;
                if (x >= powerOfTwo[mid]) {
                    left = mid;
                } else {
                    right = mid;
                }
            }

            x -= powerOfTwo[left];
            sum++;
        }

        cout << sum - 1 << endl;
    }

    return 0;
}