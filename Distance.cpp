#include <cmath>
#include <iostream>

struct Point {
  double x;
  double y;
};

struct Vector {
  double x;
  double y;
  Vector(const Point& a, const Point& b) {
    x = b.x - a.x;
    y = b.y - a.y;
  }
};

double ScalPr(const Vector& a, const Vector& b) {
  return a.x * b.x + a.y * b.y;
}

double VectPr(const Vector& a, const Vector& b) {
  return a.x * b.y - a.y * b.x;
}

double Distance(const Vector& ab_vector, const Vector& ac_vector) {
  return std::abs(VectPr(ab_vector, ac_vector) / sqrt(ab_vector.x * ab_vector.x + ab_vector.y * ab_vector.y));
}
double DitancePointPoint(const Point& a, const Point& b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
  std::cout << std::showpoint;
  std::cout.precision(7);
  Point a, b, c;
  std::cin >> c.x >> c.y >> a.x >> a.y >> b.x >> b.y;
  Vector ab_vector(a, b), ba_vector(b, a), ac_vector(a, c), bc_vector(b, c);
  std::cout << std::abs(VectPr(ab_vector, ac_vector)) / DitancePointPoint(a, b) << '\n';
  if (ScalPr(ab_vector, ac_vector) > 0) {
    std::cout << std::abs(VectPr(ab_vector, ac_vector)) / DitancePointPoint(a, b) << '\n';
  } else {
    std::cout << DitancePointPoint(a, c) << '\n';
  }
  if (ScalPr(ab_vector, ac_vector) <= 0) {
    std::cout << DitancePointPoint(a, c);
  } else if (ScalPr(ba_vector, bc_vector) <= 0) {
    std::cout << DitancePointPoint(b, c);
  } else {
    std::cout << std::abs(VectPr(ab_vector, ac_vector)) / DitancePointPoint(a, b);
  }
  return 0;
}