#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::scanf;
using std::puts;
const int MAX = 100001;

struct Point {
    long long x, y;
    Point(long long x = 0, long long y = 0) : x(x), y(y) {}
};

int angle(Point a, Point b, Point c) {
    long long q = (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
    return (q > 0) - (q < 0);
}

bool inside(Point q, Point* p, int n) {
    Point a = p[1];
    if (angle(a, p[2], q) < 0 || angle(a, p[n], q) > 0) return false;

    int l = 2, r = n, m;
    while (l + 1 < r) {
        m = (l + r) / 2;
        if (angle(a, p[m], q) < 0)
            r = m;
        else
            l = m;
    }

    return angle(p[l], p[r], q) >= 0;
}

int main() {
    int n, m, k;
    long long x, y;
    Point p[MAX];

    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld %lld", &x, &y);
        p[i] = Point(x, y);
    }

    int res = 0;
    for (int i = 1; i <= m; ++i) {
        scanf("%lld %lld", &x, &y);
        if (inside(Point(x, y), p, n)) res++;
    }
    if (res < k)
        puts("NO");
    else
        puts("YES");
    return 0;
}