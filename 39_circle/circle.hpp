#include "point.hpp"
#include <stdio.h>
#include <stdlib.h>

class Circle {
private:
  Point p;
  const double r;
public:
  Circle(Point ini_p, const double ini_r);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
