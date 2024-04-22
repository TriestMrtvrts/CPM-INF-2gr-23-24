#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int main() {
    long long mx, my, ax, ay, bx, by;
    cin >> mx >> my >> ax >> ay >> bx >> by;
    if ((mx - ax) * (by - ay) == (bx - ax) * (my - ay)) {
        if (min(ay, by) <= my && (max(ay, by) >= my) && min(ax, bx) <= mx && max(ax, bx) >= mx) {
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
    return 0;
}