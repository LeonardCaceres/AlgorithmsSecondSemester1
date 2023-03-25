#include <iostream>
#include <cmath>

/*
В двух строках входного файла заданы по четыре целых числа, не превосходящих по модулю 10 000, — координаты начала и конца первого вектора, затем второго.

В каждой строке выходного файла — ответ на соответствующий пункт задачи с точностью не менее 10-6.
                Длину первого и второго вектора (два числа)
                Вектор, образованный сложением данных двух векторов
                Скалярное и векторное произведения данных векторов
                Площадь треугольника, построенного из этих векторов
*/

struct Vector {
  double x;
  double y;
};

double ScalarProduct(double x1, double y1, double x2, double y2) {
  return x1 * x2 + y1 * y2;
}
double VectorProduct(double x1, double y1, double x2, double y2) {
  return x1 * y2 - x2 * y1;
}
double AreaOfTriangle(double x1, double y1, double x2, double y2) {
  double x = VectorProduct(x1, y1, x2, y2);
  return std::abs(x) / 2;
}
void SumOfTwoVectors(double x1, double y1, double x2, double y2) {
  std::cout << x1 + x2 << ' ' << y1 + y2 << '\n';
}
double PrintVectorLenght(double x, double y) {
  double result = x * x + y * y;
  return sqrt(result);
}
int main() {
  std::cout << std::showpoint;
  std::cout.precision(7);
  double x1_s, y1_s, x1_f, y1_f;
  double x2_s, y2_s, x2_f, y2_f;
  std::cin >> x1_s >> y1_s >> x1_f >> y1_f;
  std::cin >> x2_s >> y2_s >> x2_f >> y2_f;
  Vector first;
  Vector second;
  first.x = x1_f - x1_s;
  first.y = y1_f - y1_s;
  second.x = x2_f - x2_s;
  second.y = y2_f - y2_s;
  std::cout << PrintVectorLenght(first.x, first.y) << ' ';
  std::cout << PrintVectorLenght(second.x, second.y) << '\n';
  SumOfTwoVectors(first.x, first.y, second.x, second.y);
  std::cout << ScalarProduct(first.x, first.y, second.x, second.y) << ' ';
  std::cout << VectorProduct(first.x, first.y, second.x, second.y) << '\n';
  std::cout << AreaOfTriangle(first.x, first.y, second.x, second.y);
}