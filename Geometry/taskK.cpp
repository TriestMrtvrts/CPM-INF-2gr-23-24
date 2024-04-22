using namespace std;

struct Point {
    double x, y;
};

struct Line {
    double a, b, c;

    void create(Point p1, Point p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = p2.x * p1.y - p2.y * p1.x;
    }
};

int main() {
    Point A, B, C;
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;

    Line v1, v2, res;
    v1.create(A, B);
    v2.create(A, C);

    res.b = v1.b * sqrt(v2.a * v2.a + v2.b * v2.b) + v2.b * sqrt(v1.a * v1.a + v1.b * v1.b);
    res.a = v1.a * sqrt(v2.a * v2.a + v2.b * v2.b) + v2.a * sqrt(v1.a * v1.a + v1.b * v1.b);
    res.c = v1.c * sqrt(v2.a * v2.a + v2.b * v2.b) + v2.c * sqrt(v1.a * v1.a + v1.b * v1.b);

    cout << fixed;
    cout.precision(7);
    cout << res.a << " " << res.b << " " << res.c;

    return 0;
}