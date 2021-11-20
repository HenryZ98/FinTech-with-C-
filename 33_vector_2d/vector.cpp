#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */

void Vector2D::initVector(double init_x, double init_y) {
  x = init_x;
  y = init_y;
}

double Vector2D::getMagnitude() const {
  double mag = std::sqrt((x*x) + (y*y));
  return mag;
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D ans1;
  ans1.x = x + rhs.x;
  ans1.y = y + rhs.y;
  return ans1;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x = x + rhs.x;
  y = y + rhs.y;
  return *this;
  
}

double Vector2D::dot(const Vector2D & rhs) const {
  double dotp;
  dotp = x * rhs.x + y * rhs.y;
  return dotp;
}

void Vector2D::print() const {
  printf("<%.2f, %.2f>", x, y);
}


  
