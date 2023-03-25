#include <iostream>

struct Point {
  int64_t x;
  int64_t y;
  Point() {
    x = 0;
    y = 0;
  }
  Point(int64_t a, int64_t b) {
    x = a;
    y = b;
  }
};

struct Vector {
  int64_t x;
  int64_t y;
  Vector(Point a, Point b) {
    x = b.x - a.x;
    y = b.y - a.y;
  }
  Vector() {
    x = 0;
    y = 0;
  }
};

int64_t VectProduct(const Vector& a, const Vector& b) {
  return (a.x * b.y - a.y * b.x);
}

void PrintPolygonArea(int64_t area) {
  if (std::abs(area) % 2 == 1) {
    std::cout << std::abs(area) / 2 << ".5";
  } else {
    std::cout << std::abs(area) / 2 << ".0";
  }
}

int main() {
  int64_t n;
  std::cin >> n;
  Point a;
  std::cin >> a.x >> a.y;
  Point first(a.x, a.y);
  Point reference_point(a.x, a.y);
  int64_t square = 0;
  Vector ref_a, ref_b;
  Point b;
  for (int64_t i = 0; i < n - 1; ++i) {
    std::cin >> b.x >> b.y;
    ref_a.x = a.x - reference_point.x;
    ref_a.y = a.y - reference_point.y;
    ref_b.x = b.x - reference_point.x;
    ref_b.y = b.y - reference_point.y;
    square += VectProduct(ref_a, ref_b);
    a.x = b.x;
    a.y = b.y;
  }
  Vector ref_first(reference_point, first);
  square += VectProduct(ref_a, ref_first);
  PrintPolygonArea(square);
  return 0;
}