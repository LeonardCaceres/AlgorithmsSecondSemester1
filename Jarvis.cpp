#include <cmath>
#include <vector>
#include <iostream>

struct Point {
  int64_t x_p;
  int64_t y_p;
  Point() {
    x_p = 0;
    y_p = 0;
  }
  Point(const Point& a) {
    x_p = a.x_p;
    y_p = a.y_p;
  }
  Point& operator=(const Point& other) {
    if (this == &other) {
      return *this;
    }
    x_p = other.x_p;
    y_p = other.y_p;
    return *this;
  }
  bool operator==(const Point& other) {
    return (this->x_p == other.x_p) && (this->y_p == other.y_p);
  }
};

struct Vector {
  int64_t x_v;
  int64_t y_v;
  Vector() {
    x_v = 0;
    y_v = 1;
  }
  Vector(Point a, Point b) {
    x_v = b.x_p - a.x_p;
    y_v = b.y_p - a.y_p;
  }
  Vector(const int64_t& a, const int64_t& b) {
    x_v = a;
    y_v = b;
  }
};

int64_t ScalarPr(const Vector& a, const Vector& b) {
  return a.x_v * b.x_v + a.y_v * b.y_v;
}

int64_t VectorPrInt(const Vector& a, const Vector& b) {
  return (a.x_v * b.y_v - a.y_v * b.x_v);
}

double Lenght(const Vector& a) {
  return (std::sqrt(a.x_v * a.x_v + a.y_v * a.y_v));
}

std::ostream& operator<<(std::ostream& os, const std::vector<Point>& polygon) {
  os << polygon.size() << '\n';
  for (uint64_t i = 0; i < polygon.size(); ++i) {
    os << polygon[i].x_p << ' ' << polygon[i].y_p << '\n';
  }
  return os;
}

void RedefinitionVector(Vector& ab, Vector& bc, const Point& first_point, const Point& polyg_1, const Point& polyg_2) {
  ab.x_v = polyg_1.x_p - first_point.x_p;
  ab.y_v = polyg_1.y_p - first_point.y_p;
  bc.x_v = polyg_2.x_p - first_point.x_p;
  bc.y_v = polyg_2.y_p - first_point.y_p;
}

uint64_t SquareCalculation(const std::vector<Point>& pol) {
  uint64_t square = 0;
  Point first_point(pol[0]);
  Vector ab;
  Vector bc;
  for (uint64_t i = 1; i < pol.size(); ++i) {
    RedefinitionVector(ab, bc, first_point, pol[i % pol.size()], pol[(i + 1) % pol.size()]);
    square -= VectorPrInt(ab, bc);
  }
  return square;
}

void SortNextPoint(std::vector<Point>& arr, std::vector<Vector>& op_before, const Point& o, Vector& for_sort_vector) {
  Vector enter;
  for (uint64_t i = 0; i < arr.size(); ++i) {
    enter.x_v = arr[i].x_p - o.x_p;
    enter.y_v = arr[i].y_p - o.y_p;
    op_before.push_back(enter);
  }
  for (uint64_t i = 0; i < op_before.size() - 1; ++i) {
    if (arr[i + 1] == o) {
      std::swap(arr[i], arr[i + 1]);
      std::swap(op_before[i], op_before[i + 1]);
      continue;
    }
    if (!(Lenght(op_before[i]) == 0 && Lenght(op_before[i]) == 0)) {
      if (ScalarPr(for_sort_vector, op_before[i]) / (Lenght(op_before[i]) * Lenght(for_sort_vector)) -
              (ScalarPr(for_sort_vector, op_before[i + 1]) / (Lenght(op_before[i + 1]) * Lenght(for_sort_vector))) <
          0.000000000001) {
        if (Lenght(op_before[i]) - Lenght(op_before[i + 1]) > 0.000000000001) {
          std::swap(arr[i], arr[i + 1]);
          std::swap(op_before[i], op_before[i + 1]);
        }
      }
      if (ScalarPr(for_sort_vector, op_before[i]) / (Lenght(op_before[i]) * Lenght(for_sort_vector)) -
              (ScalarPr(for_sort_vector, op_before[i + 1]) / (Lenght(op_before[i + 1]) * Lenght(for_sort_vector))) >
          0.000000000001) {
        std::swap(arr[i], arr[i + 1]);
        std::swap(op_before[i], op_before[i + 1]);
      }
    } else if (Lenght(op_before[i + 1]) == 0) {
      std::swap(arr[i], arr[i + 1]);
      std::swap(op_before[i], op_before[i + 1]);
    }
  }
}

std::vector<Point> ShellCalculation(std::vector<Point>& arr) {
  std::vector<Point> shell;
  Point o(arr[0]);
  for (uint64_t i = 1; i < arr.size(); ++i) {
    if (o.x_p > arr[i].x_p) {
      o = arr[i];
    }
    if (o.x_p == arr[i].x_p) {
      if (o.y_p > arr[i].y_p) {
        o = arr[i];
      }
    }
  }
  shell.push_back(o);
  std::vector<Vector> op_before;
  Vector for_sort_vector(-1, 1000);
  SortNextPoint(arr, op_before, o, for_sort_vector);
  shell.push_back(arr.back());
  for_sort_vector.x_v = arr.back().x_p - o.x_p;
  for_sort_vector.y_v = arr.back().y_p - o.y_p;
  Point a(arr.back());
  std::vector<Vector> ap;
  while (true) {
    SortNextPoint(arr, ap, a, for_sort_vector);
    for_sort_vector.x_v = arr.back().x_p - a.x_p;
    for_sort_vector.y_v = arr.back().y_p - a.y_p;
    a = arr.back();
    if (a == o) {
      return shell;
    }
    shell.push_back(a);
    ap.clear();
  }
}

int main() {
  uint64_t n;
  std::cin >> n;
  std::vector<Point> arr;
  Point enter;
  for (uint64_t i = 0; i < n; ++i) {
    std::cin >> enter.x_p >> enter.y_p;
    arr.push_back(enter);
  }
  std::vector<Point> shell = (ShellCalculation(arr));
  std::cout << shell;
  if (SquareCalculation(shell) % 2 == 1) {
    std::cout << SquareCalculation(shell) / 2 << ".5";
  } else {
    std::cout << SquareCalculation(shell) / 2 << ".0";
  }
  return 0;
}