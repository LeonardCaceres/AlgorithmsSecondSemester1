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
  Vector() {
    x = 0;
    y = 0;
  }
  Vector(Point a, Point b) {
    x = b.x - a.x;
    y = b.y - a.y;
  }
};

int64_t VectPr(const Vector& a, const Vector& b) {
  return (a.x * b.y - a.y * b.x);
}

void VectorDefinition(Vector& ac, Vector& ab, const Point& a, const Point& b, const Point& c) {
  ac.x = c.x - a.x;
  ac.y = c.y - a.y;
  ab.x = b.x - a.x;
  ab.y = b.y - a.y;
}

void PointDefinition(Point& a, Point& b, const Point& c) {
  a.x = b.x;
  a.y = b.y;
  b.x = c.x;
  b.y = c.y;
}

int64_t Sign(const int64_t& a) {
  int ret = 1;
  if (a < 0) {
    ret = -1;
  } else if (a == 0) {
    ret = 0;
  }
  return ret;
}

bool IsItConvex(const int64_t n) {
  bool is_it_convex = true;
  Point a, b, c;
  std::cin >> a.x >> a.y >> b.x >> b.y;
  Point first_point(a.x, a.y), second_point(b.x, b.y), third_point;
  Vector ab, ac;
  if (a.x == b.x && a.y == b.y) {
    is_it_convex = false;
  }
  int64_t sign_vect_pr = 0;
  if (n > 2) {
    bool flag_for_third_point = true;
    for (int64_t i = 0; i < n - 2; ++i) {
      std::cin >> c.x >> c.y;
      if (flag_for_third_point) {
        third_point.x = c.x;
        third_point.y = c.y;
        flag_for_third_point = false;
      }
      if (c.x == b.x && c.y == b.y) {
        is_it_convex = false;
      }
      VectorDefinition(ac, ab, a, b, c);
      if (sign_vect_pr * Sign(VectPr(ab, ac)) < 0) {
        is_it_convex = false;
      }
      PointDefinition(a, b, c);
      if (VectPr(ab, ac) != 0) {
        sign_vect_pr = Sign(VectPr(ab, ac));
      }
    }
    c.x = first_point.x;
    c.y = first_point.y;
    VectorDefinition(ac, ab, a, b, c);
    if (sign_vect_pr * Sign(VectPr(ab, ac)) < 0) {
      is_it_convex = false;
    }
    if (c.x == b.x && c.y == b.y) {
      is_it_convex = false;
    }
    PointDefinition(a, b, c);
    c.x = second_point.x;
    c.y = second_point.y;
    VectorDefinition(ac, ab, a, b, c);
    if (sign_vect_pr * Sign(VectPr(ab, ac)) < 0) {
      is_it_convex = false;
    }
    if (c.x == b.x && c.y == b.y) {
      is_it_convex = false;
    }
  }
  return is_it_convex;
}

int main() {
  int64_t n;
  std::cin >> n;
  if (IsItConvex(n)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}