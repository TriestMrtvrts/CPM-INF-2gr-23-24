#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y, index;

    Point(int x = 0, int y = 0, int index = -1) : x(x), y(y), index(index) {}

    int squaredLength() const {
        return x * x + y * y;
    }


    Point subtract(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }

    int crossProduct(const Point& other) const {
        return x * other.y - y * other.x;
    }

    bool equals(const Point& other) const {
        return x == other.x && y == other.y && index == other.index;
    }
};

istream& operator>>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

ostream& operator<<(ostream& out, const Point& p) {
    out << p.x << ' ' << p.y;
    return out;
}

bool comparePoints(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

vector<Point> points;
vector<int> labels;

bool canUse(const Point& start, const Point& current, const Point& candidate) {
    Point vect1 = current.subtract(start), vect2 = candidate.subtract(start);
    return vect1.crossProduct(vect2) > 0 || (vect1.crossProduct(vect2) == 0 && vect1.squaredLength() > vect2.squaredLength());
}

void findHull(int startIndex, int label) {
    Point initial = points[startIndex], current;
    do {
        current = initial;
        for (const auto& p : points) {
            if (current.equals(p) || labels[p.index] != -1) continue;
            if (canUse(initial, current, p) || current.equals(initial)) {
                current = p;
            }
        }
        labels[current.index] = label;
        initial = current;
    } while (!initial.equals(points[startIndex]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    points.resize(n);
    labels.resize(n, -1);

    for (int i = 0; i < n; ++i) {
        cin >> points[i];
        points[i].index = i;
    }

    sort(points.begin(), points.end(), comparePoints);

    int labelCount = 0;
    for (int i = 0; i < n; ++i) {
        if (labels[points[i].index] == -1) {
            findHull(i, ++labelCount);
        }
    }

    for (int label : labels) {
        cout << label << '\n';
    }
}