#include "point.hpp"
#include <cstdio>
#include <cstdlib>
#include <cmath>


Point::Point():x(0), y(0) {}

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double ans;
  double x1;
  double y1;
  double x2;
  double y2;
  if(p.x >= x) {
    x1 = p.x;
    x2 = x;
  }
  else {
    x1 = x;
    x2 = p.x;
  }
  if(p.y >= y) {
    y1 = p.y;
    y2 = y;
  }
  else {
    y1 = y;
    y2 = p.y;
  }
  ans = std::sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
  return ans;
}
