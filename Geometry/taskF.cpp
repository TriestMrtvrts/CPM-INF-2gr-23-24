#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

static const double eps = 1e-7;
class Dot {
    double x, y;
 public:
    Dot(double x = 0, double y = 0) { this->x = x; this->y = y; }
    double get_x() const {return x;}
    double get_y() const {return y;}
};
class Vect {
    double x, y;
 public:
    Vect(double x = 0, double y = 0) { this->x = x; this->y = y; }
    Vect(const Dot & a, const Dot & b) {x = b.get_x() - a.get_x(); y = b.get_y() - a.get_y();}
    Vect operator+(const Vect & a);
    double get_x() const {return x;}
    double get_y() const {return y;}
    double get_mod() const {return sqrt(x * x + y * y);}
};
Vect Vect::operator+(const Vect & a) {
    Vect res(this->get_x() + a.get_x(), this->get_y() + a.get_y());
    return res;
}
Vect operator* (double a, const Vect & b) {
    Vect res(b.get_x() * a, b.get_y() * a);
    return res;
}
Vect operator* (const Vect & b, double a) {
    Vect res(b.get_x() * a, b.get_y() * a);
    return res;
}
Dot operator+ (const Dot & dot, const Vect & v) {
    return Dot(dot.get_x() + v.get_x(), dot.get_y() + v.get_y());
}
double scalar_product(const Vect & a, const Vect & b) {
    return (a.get_x() * b.get_x() + a.get_y() * b.get_y());
}
bool is_collinear(const Vect & a, const Vect & b) {
    return abs((abs(scalar_product(a, b)) - a.get_mod() * b.get_mod())) < ::eps;
}
class Line {
    Vect dir;
    Dot dot;
 public:
    Line() { dir = Vect(); dot = Dot(); }
    Line(const Dot & a, const Dot & b);
    Line(const Vect & v, const Dot & dot) {dir = v; this->dot = dot;}
    Vect get_vect() const {return dir;}
    Dot get_dot() const {return dot;}
};
Line::Line(const Dot & a, const Dot & b) {
    dir = Vect(a, b);
    dot = a;
}
Dot
i_hate_conditions(const Line & a, const Line & b) {
    double xa = a.get_dot().get_x(), ya = a.get_dot().get_y();
    double xc = a.get_vect().get_x(), yc = a.get_vect().get_y();
    double xb = b.get_dot().get_x(), yb = b.get_dot().get_y();
    double xd = b.get_vect().get_x(), yd = b.get_vect().get_y();
    double t = ((xa - xb) / xd + (yb - ya) / yc * xc / xd) / (1 - yd * xc / yc / xd);
    Dot res = b.get_dot() + t * b.get_vect();
    return res;
}
Dot
i_hate_conditions_new(const Line & a, const Line & b) {
    double xa = a.get_dot().get_x(), ya = a.get_dot().get_y();
    double xc = a.get_vect().get_x(), yc = a.get_vect().get_y();
    double xb = b.get_dot().get_x(), yb = b.get_dot().get_y();
    double xd = b.get_vect().get_x(), yd = b.get_vect().get_y();
    Dot res;
    if (((abs(xc) < ::eps) && (abs(yd) < ::eps)) || ((abs(xd) < ::eps) && (abs(yc) < ::eps))) {
        double x, y;
        if (abs(a.get_vect().get_x()) < ::eps) {
            x = a.get_dot().get_x();
            y = b.get_dot().get_y();
        } else {
            x = b.get_dot().get_x();
            y = a.get_dot().get_y();
        }
        res = Dot(x, y);
    } else if (abs(yd) < ::eps) {
        double t = (xa - xb + (yb - ya) / yc * xc) / (xd - yd / yc * xc);
        res = b.get_dot() + b.get_vect() * t;
    } else {
        double k = (xa - xb - (ya - yb) / yd * xd) / (yc / yd * xd - xc);
        res = a.get_dot() + a.get_vect() * k;
    }
    return res;
}
void intersect_lines(const Line & a, const Line & b) {
    Vect v1 = a.get_vect();
    Vect v2 = b.get_vect();
    if (is_collinear(v1, v2)) {
        Vect dif(a.get_dot(), b.get_dot());
        if (is_collinear(dif, v1)) {
            cout << "2" << endl;
        } else {
            cout << "0" << endl;
        }
    } else {
        Dot res = i_hate_conditions_new(a, b);
        cout << fixed;
        cout << "1 " << setprecision(5) << res.get_x() << ' ' << res.get_y()<< endl;
    }
}
int main(int argc, char const *argv[]) {
    double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    Line l1(Dot(x1, y1), Dot(x2, y2));
    cin >> x1 >> y1 >> x2 >> y2;
    Line l2(Dot(x1, y1), Dot(x2, y2));
    intersect_lines(l1, l2);
    return 0;
}