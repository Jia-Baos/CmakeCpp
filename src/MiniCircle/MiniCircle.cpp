#include "./MiniCircle.hpp"

// 判断半径大小
int Judge(const double a, const double b) {
  if (std::abs(a - b) < kEps) {
    return 0;
  }
  if (a < b) {
    return -1;
  }
  return 1;
}

// 向量旋转，a表示顺时针旋转的弧度值
Point Rotate(const Point &p1, const double a) {
  return {p1.x * std::cos(a) + p1.y * std::sin(a), -p1.x * std::sin(a) + p1.y * std::cos(a)};
}

// 求两点之间距离
double Distance(const Point &p1, const Point &p2) {
  const double dx = p1.x - p2.x;
  const double dy = p1.y - p2.y;
  return std::sqrt(dx * dx + dy * dy);
}

// 求两直线的交点
Point Intersection(const Point &p1, const Point &v1, const Point &p2, const Point &v2) {
  Point result;
  if (v1 * v2 != 0) {
    const Point temp = p1 - p2;
    const double ratio = (v2 * temp) / (v1 * v2);
    result = p1 + v1 * ratio;
  }
  return result;
}

// 求两点之间连线的中垂线
std::pair<Point, Point> MidPerpendicular(const Point &p1, const Point &p2) {
  const Point mid = (p1 + p2) / 2;
  // 垂直时再利用旋转求解会降低精度
  // const Point rotate = Rotate(p1 - p2, PI / 2);
  const Point rotate = {-p1.y + p2.y, p1.x - p2.x};
  return {mid, rotate};
}

// 已知三点求外接圆
Circle MiniCircle(Point p1, Point p2, Point p3) {
  auto m1 = MidPerpendicular(p1, p2);
  auto m2 = MidPerpendicular(p1, p3);
  Point center_point = Intersection(m1.first, m1.second, m2.first, m2.second);
  double radius = Distance(center_point, p1);
  return {center_point, radius};
}

Circle MinimumCoveringCircle(const std::vector<Point> &points, const int npoints) {
  // 初始化圆，圆心为points[0]，半径为0
  Circle circle(points[0], 0.0);
  for (int i = 1; i < npoints; i++) {
    if (Judge(circle.radius, Distance(circle.center, points[i])) == -1) {
      // 如果points[i]在圆的外部，重新指定圆心的位置
      circle = {points[i], 0};
      for (int j = 0; j < i; j++) {
        if (Judge(circle.radius, Distance(circle.center, points[j])) == -1) {
          // 如果points[j]在圆的外部，利用points[i]，points[j]生成一个最小圆
          circle = {(points[i] + points[j]) / 2, Distance(points[i], points[j]) / 2};
          for (int k = 0; k < j; k++) {
            // 如果points[k]在圆的外部，利用points[i]，points[j]，points[k]生成一个最小圆
            if (Judge(circle.radius, Distance(circle.center, points[k])) == -1) {
              circle = MiniCircle(points[i], points[j], points[k]);
            }
          }
        }
      }
    }
  }
  return circle;
}
