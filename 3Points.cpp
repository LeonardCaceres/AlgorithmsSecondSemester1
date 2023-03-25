#include <iostream>

struct Point {
  double x;
  double y;
};
struct Vector {
  double x;
  double y;
  Vector(Point b, Point c) {
    x = b.x - c.x;
    y = b.y - c.y;
  }
};
double VectorProduct(Vector cb, Vector ca) {
  return cb.x * ca.y - cb.y * ca.x;
}
double SkalarProduct(Vector cb, Vector ca) {
  return cb.x * ca.x + cb.y * ca.y;
}
bool BelongsSegment(Vector cb, Vector ca) {
  return (VectorProduct(cb, ca) == 0 && SkalarProduct(cb, ca) <= 0);
}
bool BelongsLine(Vector cb, Vector ca) {
  return (VectorProduct(cb, ca) == 0);
}
bool BelongsRay(Vector cb, Vector ca, Vector ba, Vector bc) {
  return (VectorProduct(cb, ca) == 0 && (SkalarProduct(cb, ca) <= 0 || SkalarProduct(bc, ba) <= 0));
}
int main() {
  Point a, b, c;
  std::cin >> c.x >> c.y >> a.x >> a.y >> b.x >> b.y;
  Vector cb(c, b), ca(c, a);
  Vector ba(b, a), bc(b, c);
  if (BelongsLine(cb, ca)) {
    std::cout << "YES" << '\n';
  } else {
    std::cout << "NO" << '\n';
  }
  if (BelongsRay(cb, ca, ba, bc)) {
    std::cout << "YES" << '\n';
  } else {
    std::cout << "NO" << '\n';
  }
  if (BelongsSegment(cb, ca)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}