#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
};
Point subtractPoints(const Point& a, const Point& b) {
    return {a.x - b.x, a.y - b.y};
}
double calculateVectorLength(const Point& vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}
Point rotateClockwise90(const Point& vector) {
    return {vector.y, -vector.x};
}
Point rotateCounterClockwise90(const Point& vector) {
    return {-vector.y, vector.x};
}
int main() {
    Point point1, point2;
    cin >> point1.x >> point1.y >> point2.x >> point2.y;
    double vectorLength;
    cin >> vectorLength;
    Point vectorAB = subtractPoints(point2, point1);
    Point normalizedVectorAB = {vectorAB.x / calculateVectorLength(vectorAB),
                                vectorAB.y / calculateVectorLength(vectorAB)};
    Point vectorCD = {normalizedVectorAB.x * vectorLength, normalizedVectorAB.y * vectorLength};
    Point rotatedClockwise90 = rotateClockwise90(vectorAB);
    Point rotatedCounterClockwise90 = rotateCounterClockwise90(vectorAB);
    cout << fixed << setprecision(4) << vectorAB.x << " " << vectorAB.y << endl;
    cout << normalizedVectorAB.x << " " << normalizedVectorAB.y << endl;
    cout << vectorCD.x << " " << vectorCD.y << endl;
    cout << rotatedClockwise90.x << " " << rotatedClockwise90.y << endl;
    cout << rotatedCounterClockwise90.x << " " << rotatedCounterClockwise90.y << endl;
    return 0;
}