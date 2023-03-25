#include <iostream>
#include <cmath>

struct Line {
  double a;
  double b;
  double c;
  Line(double ai, double bi, double ci) {
    a = ai;
    b = bi;
    c = ci;
  }
};
struct Point {
  double x;
  double y;
};

double Determinant(const Line& line_1, const Line& line_2) {
  return line_1.a * line_2.b - line_1.b * line_2.a;
}
void PrintGuidingVector(const Line& line_1, const Line& line_2) {
  std::cout << line_1.b << ' ' << -line_1.a << '\n';
  std::cout << line_2.b << ' ' << -line_2.a << '\n';
}
double Lenght(const Line& line_1, const Line& line_2) {
  double x0;
  double y0;
  if (line_1.a != 0) {
    x0 = -line_1.c / line_1.a;
    y0 = 0;
  } else {
    y0 = -line_1.c / line_1.b;
    x0 = 0;
  }
  return (line_2.a * x0 + line_2.b * y0 + line_2.c) / (sqrt(line_2.a * line_2.a + line_2.b * line_2.b));
}
Point IntersectionPoint(const Line& line_1, const Line& line_2) {
  Point i;
  i.x = (line_1.b * line_2.c - line_1.c * line_2.b) / Determinant(line_1, line_2);
  i.y = (line_1.c * line_2.a - line_1.a * line_2.c) / Determinant(line_1, line_2);
  return i;
}
int main() {
  std::cout << std::showpoint;
  std::cout.precision(7);
  double a1, a2;
  double b1, b2;
  double c1, c2;
  std::cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
  const Line line_1(a1, b1, c1);
  const Line line_2(a2, b2, c2);
  PrintGuidingVector(line_1, line_2);
  if (Determinant(line_1, line_2) == 0) {
    std::cout << Lenght(line_1, line_2);
  } else {
    Point a;
    a = IntersectionPoint(line_1, line_2);
    std::cout << a.x << ' ' << a.y;
  }
  return 0;
}