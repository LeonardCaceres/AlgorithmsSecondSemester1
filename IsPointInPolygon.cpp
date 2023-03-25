#include <iostream>
#include <vector>

struct Vector;

struct Point {
  int64_t x_p;
  int64_t y_p;
  Point() {
    x_p = 0;
    y_p = 0;
  }
  Point(int64_t a, int64_t b) {
    x_p = a;
    y_p = b;
  }
  Point& operator=(const Point& other) {
    if (this != &other) {
      x_p = other.x_p;
      y_p = other.y_p;
    }
    return *this;
  }
  Vector operator-(const Point& other);
};

struct Vector {
  int64_t x_v;
  int64_t y_v;
  Vector() {
    x_v = 1000;
    y_v = 999;
  }
  Vector(Point a, Point b) {
    x_v = b.x_p - a.x_p;
    y_v = b.y_p - a.y_p;
  }
};

Vector Point::operator-(const Point& other) {
  Vector ab;
  ab.x_v = this->x_p - other.x_p;
  ab.y_v = this->y_p - other.y_p;
  return ab;
}

struct Ray {
  Point o;
  Vector op;
  explicit Ray(Point a) {
    o.x_p = a.x_p;
    o.y_p = a.y_p;
    Vector op;
  }
};

struct Polygon {
  std::vector<Point> arr;
  int64_t size;
  explicit Polygon(const int64_t& n) {
    size = n;
  }
};

struct Segment {
  Point a_s;
  Point b_s;
  Segment(Point a, Point b) {
    a_s = a;
    b_s = b;
  }
};

void DefinitionPolygon(Polygon& pol) {
  Point enter;
  for (int64_t i = 0; i < pol.size; ++i) {
    std::cin >> enter.x_p >> enter.y_p;
    pol.arr.push_back(enter);
  }
}

int64_t ScalarPr(const Vector& a, const Vector& b) {
  return a.x_v * b.x_v + a.y_v * b.y_v;
}

int64_t VectorPr(const Vector& a, const Vector& b) {
  return a.x_v * b.y_v - a.y_v * b.x_v;
}

int64_t Sign(const int64_t& a) {
  int64_t k = 1;
  if (a < 0) {
    k = -1;
  } else if (a == 0) {
    k = 0;
  }
  return k;
}

bool PointInSegment(const Point& o, const Segment& ab) {
  Vector oa(o, ab.a_s);
  Vector ob(o, ab.b_s);
  return (VectorPr(oa, ob) == 0 && ScalarPr(oa, ob) < 0);
}

bool PointInRay(const Ray& ray, const Point& b) {
  Vector ob(ray.o, b);
  return (ScalarPr(ray.op, ob) >= 0 && VectorPr(ray.op, ob) == 0);
}

bool IsSegmentRay(const Ray& ray, const Segment& ab_seg) {
  Vector oa(ray.o, ab_seg.a_s), ob(ray.o, ab_seg.b_s);
  Vector ao(ab_seg.a_s, ray.o), bo(ab_seg.b_s, ray.o);
  Vector ab(ab_seg.a_s, ab_seg.b_s);
  return ((Sign(VectorPr(ray.op, oa)) * Sign(VectorPr(ray.op, ob)) < 0) &&
          (Sign(VectorPr(ao, ab)) * Sign(VectorPr(ray.op, ab)) < 0));
}

bool IsPoligonConvex(Polygon pol, const Ray& ray) {
  Vector oa(ray.o, pol.arr[0]);
  Vector ob(ray.o, pol.arr[1]);
  Segment ab_seg(pol.arr[0], pol.arr[1]);
  int64_t counter = 0;
  bool is_on_the_border = false;
  for (int64_t i = 1; i < pol.size; ++i) {
    if (IsSegmentRay(ray, ab_seg) && (!PointInSegment(ray.o, ab_seg))) {
      counter++;
    } else if (PointInSegment(ray.o, ab_seg)) {
      counter++;
      is_on_the_border = true;
    }
    oa = pol.arr[i] - ray.o;
    ob = pol.arr[(i + 1) % pol.size] - ray.o;
    ab_seg.a_s = pol.arr[i];
    ab_seg.b_s = pol.arr[(i + 1) % pol.size];
  }
  if (IsSegmentRay(ray, ab_seg) && (!PointInSegment(ray.o, ab_seg))) {
    counter++;
  } else if (PointInSegment(ray.o, ab_seg)) {
    counter++;
    is_on_the_border = true;
  }
  Point b(pol.arr[pol.size - 1].x_p, pol.arr[pol.size - 1].y_p);
  Point a(pol.arr[0].x_p, pol.arr[0].y_p);
  Point c(pol.arr[1].x_p, pol.arr[1].y_p);
  Vector ba(b, a);
  Vector bc(b, c);
  oa = pol.arr[pol.size - 1] - ray.o;
  Vector oc(ray.o, pol.arr[1]);
  for (int64_t i = 0; i < pol.size; ++i) {
    if (PointInRay(ray, b)) {
      if (VectorPr(ray.op, oa) * VectorPr(ray.op, oc) > 0) {
        counter += 2;
      } else if (VectorPr(ray.op, oa) * VectorPr(ray.op, oc) < 0) {
        counter++;
      } else if (PointInRay(ray, a) || PointInRay(ray, c)) {
        counter += 0;
      }
    }
    if (ray.o.x_p == b.x_p && ray.o.y_p == b.y_p) {
      is_on_the_border = true;
    }
    a = b;
    b = c;
    c = pol.arr[(i + 1) % pol.size];
    ba = a - b;
    bc = c - b;
    oa = pol.arr[i] - ray.o;
    oc = pol.arr[(i + 2) % pol.size] - ray.o;
  }
  if (PointInRay(ray, b)) {
    if (VectorPr(ray.op, oa) * VectorPr(ray.op, oc) > 0) {
      counter += 2;
    } else if (VectorPr(ray.op, oa) * VectorPr(ray.op, oc) < 0) {
      counter++;
    } else if (PointInRay(ray, a) || PointInRay(ray, c)) {
      counter += 0;
    }
  }
  if (ray.o.x_p == b.x_p && ray.o.y_p == b.y_p) {
    is_on_the_border = true;
  }
  if (is_on_the_border) {
    counter = 1;
  }
  return counter % 2;
}

int main() {
  int64_t n;
  Point o;
  std::cin >> n >> o.x_p >> o.y_p;
  Ray op(o);
  Polygon poligon(n);
  DefinitionPolygon(poligon);
  if (IsPoligonConvex(poligon, op)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}