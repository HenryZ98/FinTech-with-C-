#include "circle.hpp"
#include <cstdio>
#include <cstdlib>
#include <math.h>

Circle::Circle(Point ini_p, const double ini_r): p(ini_p), r(ini_r) {}
void Circle::move(double dx, double dy) {
  p.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double ans;
  double d = p.distanceFrom(otherCircle.p);
  double rs = r;
  double rb = otherCircle.r;
  if(rb < rs) {
    rb = r;
    rs = otherCircle.r;
  }
  
  if(d >= rs + rb) {
    return 0;
  }
  else if(d >= 0 && d <= (rb - rs)) {
    ans = rs * rs * M_PI;
    return ans;
  }
  else {
    double part1 = rs*rs*std::acos((d*d + rs*rs - rb*rb)/(2*d*rs));
    double part2 = rb*rb*std::acos((d*d + rb*rb - rs*rs)/(2*d*rb));
    double part3 = 0.5*std::sqrt((-d+rs+rb)*(d+rs-rb)*(d-rs+rb)*(d+rs+rb));
    ans = part1 + part2 - part3;
    return ans;
  }
}
