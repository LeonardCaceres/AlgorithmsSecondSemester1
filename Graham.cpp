#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
  int64_t x_p;
  int64_t y_p;
  static Point first_point_for_std_sort;
  Point() {
    x_p = 0;
    y_p = 0;
  }
  Point(const Point& a) {
    x_p = a.x_p;
    y_p = a.y_p;
  }
  Point& operator=(const Point& other) = default;
  bool operator<(Point& other);
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
};

struct Ray {
  Point o;
  Vector op;
  explicit Ray(const Point& a) {
    o.x_p = a.x_p;
    o.y_p = a.y_p;
    Vector op;
  }
};

struct Stack {
  std::vector<Point> stack;
  int64_t capacity;
  int64_t current;
  explicit Stack(const uint64_t& n) {
    capacity = n;
    current = -1;
  }
  void Push(const Point& a) {
    current++;
    stack.push_back(a);
  }
  void Pop() {
    current--;
  }
};

struct Polygon {
  std::vector<Point> pol;
  explicit Polygon(const Stack& stack) {
    for (int64_t i = 0; i < stack.current; ++i) {
      pol.push_back(stack.stack[i]);
    }
  }
  int64_t SquareCalculation();
};

std::ostream& operator<<(std::ostream& os, const Polygon& polygon) {
  os << polygon.pol.size() << '\n';
  for (uint64_t i = 0; i < polygon.pol.size(); ++i) {
    os << polygon.pol[i].x_p << ' ' << polygon.pol[i].y_p << '\n';
  }
  return os;
}

int64_t ScalarPrInt(const Vector& a, const Vector& b) {
  return a.x_v * b.x_v + a.y_v * b.y_v;
}

int64_t VectorPrInt(const Vector& a, const Vector& b) {
  return (a.x_v * b.y_v - a.y_v * b.x_v);
}

void DefenitionFirstPoint(const std::vector<Point>& arr, Point& o, const uint64_t& n) {
  o.x_p = arr[0].x_p;
  o.y_p = arr[0].y_p;
  for (uint64_t i = 1; i < n; ++i) {
    if (arr[i].x_p <= o.x_p) {
      o.x_p = arr[i].x_p;
      o.y_p = arr[i].y_p;
    }
  }
  for (uint64_t i = 0; i < n; ++i) {
    if (arr[i].y_p <= o.y_p && arr[i].x_p == o.x_p) {
      o.y_p = arr[i].y_p;
    }
  }
  Point::first_point_for_std_sort = o;
}

bool Point::operator<(Point& other) {
  Vector op1(first_point_for_std_sort, other);
  Vector op2(first_point_for_std_sort, *this);
  return VectorPrInt(op1, op2) > 0;
}

uint64_t PolarSort(std::vector<Point>& arr, const uint64_t& n, const Point& o) {
  Ray ray(o);
  uint64_t counter = 0;
  for (int k = 0; k < 2; ++k) {
    for (uint64_t i = 0; i < n - counter; ++i) {
      if ((o.x_p == arr[i].x_p) && (o.y_p == arr[i].y_p)) {
        std::swap(arr[i], arr[n - 1 - counter]);
        counter++;
      }
    }
  }
  std::sort(arr.begin(), arr.end() - counter);
  auto op = new Vector[n];
  for (uint64_t i = 0; i < n - counter; ++i) {
    op[i].x_v = arr[i].x_p - o.x_p;
    op[i].y_v = arr[i].y_p - o.y_p;
  }
  for (uint64_t i = 0; i < n - counter - 1; ++i) {
    if (VectorPrInt(op[i], op[i + 1]) == 0) {
      if (arr[i].x_p > arr[i + 1].x_p) {
        std::swap(arr[i], arr[i + 1]);
        std::swap(op[i], op[i + 1]);
      }
      if (arr[i].x_p == arr[i + 1].x_p) {
        if (arr[i].y_p > arr[i + 1].y_p) {
          std::swap(arr[i], arr[i + 1]);
          std::swap(op[i], op[i + 1]);
        }
      }
    }
  }
  delete[] op;
  return counter;
}

bool PolygonConvex(const Stack& polygon, const Point& i) {
  if (polygon.current < 1) {
    return true;
  }
  Vector ab(polygon.stack[polygon.current - 1], polygon.stack[polygon.current]);
  Vector ai(polygon.stack[polygon.current - 1], i);
  return (VectorPrInt(ab, ai) < 0);
}

Polygon ShellCalculationAndPrinter(Stack& polygon, std::vector<Point> arr) {
  for (int64_t i = 1; i < polygon.capacity; ++i) {
    if (PolygonConvex(polygon, arr[i])) {
      polygon.Push(arr[i]);
    } else {
      while (!(PolygonConvex(polygon, arr[i]))) {
        polygon.Pop();
      }
      polygon.Push(arr[i]);
    }
  }
  Polygon shell(polygon);
  return shell;
}

void RedefinitionVector(Vector& ab, Vector& bc, const Point& first_point, const Point& polyg_1, const Point& polyg_2) {
  ab.x_v = polyg_1.x_p - first_point.x_p;
  ab.y_v = polyg_1.y_p - first_point.y_p;
  bc.x_v = polyg_2.x_p - first_point.x_p;
  bc.y_v = polyg_2.y_p - first_point.y_p;
}

int64_t Polygon::SquareCalculation() {
  int64_t square = 0;
  Point first_point(pol[0]);
  Vector ab(first_point, pol[1]);
  Vector bc(first_point, pol[2]);
  for (uint64_t i = 2; i < pol.size() - 1; ++i) {
    square += VectorPrInt(ab, bc);
    RedefinitionVector(ab, bc, first_point, pol[i % pol.size()], pol[(i + 1) % pol.size()]);
  }
  square += VectorPrInt(ab, bc);
  RedefinitionVector(ab, bc, first_point, pol[pol.size() - 1], pol[0]);
  square += VectorPrInt(ab, bc);
  square = std::abs(square);
  return square;
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
  Point o;
  DefenitionFirstPoint(arr, o, n);
  uint64_t counter = PolarSort(arr, n, o);
  Stack polygon(n - counter + 1);
  polygon.Push(o);
  polygon.Push(arr[0]);
  Polygon shell(ShellCalculationAndPrinter(polygon, arr));
  std::cout << shell;
  if (shell.SquareCalculation() % 2 == 1) {
    std::cout << shell.SquareCalculation() / 2 << ".5";
  } else {
    std::cout << shell.SquareCalculation() / 2 << ".0";
  }
  return 0;
}