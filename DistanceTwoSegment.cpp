#include <cmath>
#include <iostream>

struct Point {
  double x;
  double y;
};

struct Vector {
  double x;
  double y;
  Vector(Point a, Point b) {
    x = b.x - a.x;
    y = b.y - a.y;
  }
};

struct Line {
  double a;
  double b;
  double c;
  Line(Vector ab_vector, Point a_point) {
    a = ab_vector.y;
    b = -ab_vector.x;
    c = -(a * a_point.x + b * a_point.y);
  }
};

double MinInDistance(const double& a, const double& b, const double& c, const double& d) {
  return std::min(std::min(a, b), std::min(c, d));
}

double DistancePointPoint(const Point& a, const Point& b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double ScalPr(const Vector& a, const Vector& b) {
  return a.x * b.x + a.y * b.y;
}

double VectPr(const Vector& a, const Vector& b) {
  return a.x * b.y - a.y * b.x;
}

double IsUnderTheLine(const Line& line, const Point& a) {
  return (line.a * a.x + line.b * a.y + line.c);
}

bool PointInRay(const Vector& a, const Vector& b) {
  return ((VectPr(a, b) == 0) && ScalPr(a, b) >= 0);
}

bool PointInSegm(const Vector& a, const Vector& b, const Vector& c, const Vector& d) {
  return (PointInRay(a, b) && PointInRay(c, d));
}

double SegmentAndPointDistance(const Vector& ab_vector, const Vector& ac_vector, const Vector& ba_vector,
                               const Vector& bc_vector, const Point& a, const Point& b, const Point& c_start) {
  double distance;
  if (ScalPr(ab_vector, ac_vector) <= 0) {
    distance = DistancePointPoint(a, c_start);
  } else if (ScalPr(ba_vector, bc_vector) <= 0) {
    distance = DistancePointPoint(b, c_start);
  } else {
    distance = std::abs(VectPr(ab_vector, ac_vector)) / (DistancePointPoint(a, b));
  }
  return distance;
}

double SegmentAndSegmentDistance(const Point& a, const Point& b, const Point& c, const Point& d) {
  Vector ab(a, b), ac(a, c), ad(a, d), bc(b, c), db(d, b), ba(b, a);
  Vector cd(c, d), ca(c, a), cb(c, b), bd(b, d), da(d, a), dc(d, c);
  double distance1, distance2, distance3, distance4;
  distance1 = SegmentAndPointDistance(ab, ac, ba, bc, a, b, c);
  distance2 = SegmentAndPointDistance(ab, ad, ba, bd, a, b, d);
  distance3 = SegmentAndPointDistance(cd, ca, dc, da, c, d, a);
  distance4 = SegmentAndPointDistance(cd, cb, dc, db, c, d, b);
  return MinInDistance(distance1, distance2, distance3, distance4);
}

bool SegmentIntersect(const Line& ab_line, const Point& c, const Point& d, const Line& cd_line, const Point& a,
                      const Point& b) {
  return IsUnderTheLine(ab_line, c) * IsUnderTheLine(ab_line, d) < 0 &&
         IsUnderTheLine(cd_line, a) * IsUnderTheLine(cd_line, b) < 0;
}

bool PointInSegmentCheaker(const Point& a, const Point& b, const Point& c, const Point& d) {
  Vector ab(a, b), ac(a, c), ad(a, d), bc(b, c), db(d, b), ba(b, a);
  Vector cd(c, d), ca(c, a), cb(c, b), bd(b, d), da(d, a), dc(d, c);
  return (PointInSegm(ab, ac, ba, bc) || PointInSegm(ab, ad, ba, bd)) || PointInSegm(cd, cb, dc, db) ||
         PointInSegm(cd, ca, dc, da);
}
int main() {
  std::cout << std::showpoint;
  std::cout.precision(7);
  Point a, b, c, d;
  std::cin >> a.x >> a.y >> b.x >> b.y;
  std::cin >> c.x >> c.y >> d.x >> d.y;
  Vector ab(a, b);
  Vector cd(c, d);
  Line ab_line(ab, a);
  Line cd_line(cd, c);
  if (SegmentIntersect(ab_line, c, d, cd_line, a, b)) {
    std::cout << 0;
  } else if ((PointInSegmentCheaker(a, b, c, d))) {
    std::cout << 0;
  } else {
    std::cout << SegmentAndSegmentDistance(a, b, c, d);
  }
  return 0;
}