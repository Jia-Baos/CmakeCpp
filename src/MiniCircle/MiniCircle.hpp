#pragma once
#ifndef MINICIRCLE_HPP
#define MINICIRCLE_HPP

#include <cmath>
#include <vector>
#include <utility>

const int kN = 100010;
const double kEps = 1e-6;
const double kPi = 3.1415926;

class Point {
 public:
  double x;
  double y;
  Point() = default;
  Point(double x, double y) : x(x), y(y) {}

  Point operator+(const Point &p) const { return Point{x + p.x, y + p.y}; }
  Point operator-(const Point &p) const { return Point{x - p.x, y - p.y}; }
  double operator*(const Point &p) const { return x * p.y - y * p.x; }
  Point operator*(const double a) const { return Point{x * a, y * a}; }
  Point operator/(const double a) const { return Point{x / a, y / a}; }
};

struct Circle {
  Point center;
  double radius;
  Circle() : center(Point{0.0, 0.0}), radius(0.0f) {}
  Circle(const Point &center, const double radius) : center(center), radius(radius) {}
};

// 判断半径大小
int Judge(const double a, const double b);

// 向量旋转，a表示顺时针旋转的弧度值
Point Rotate(const Point &p1, const double a);

// 求两点之间距离
double Distance(const Point &p1, const Point &p2);

// 求两直线的交点
Point Intersection(const Point &p1, const Point &v1, const Point &p2, const Point &v2);

// 求两点之间连线的中垂线
std::pair<Point, Point> MidPerpendicular(const Point &p1, const Point &p2);

// 已知三点求外接圆
Circle MiniCircle(Point p1, Point p2, Point p3);

// 最小覆盖圆
Circle MinimumCoveringCircle(const std::vector<Point> &points, const int npoints);

#endif  // !MINICIRCLE_HPP
