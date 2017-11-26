#pragma once

#include "figure.h"

namespace figfit
{

class Point : public Figure, public Vec
{
public:
  Point(double x = 0.0, double y = 0.0) :
    Vec(x, y)
  {}

  Point(const Point &p) :
    Vec(p.x, p.y)
  {}

  virtual Vec normalTo(const Point &p) const {
    Vec n = p - *this;
    n.normalize();
    return n;
  }

  virtual double distanceSquaredTo(const Point &point) const {
    Vec p = point - *this;
    return p.lengthSquared();
  }

  virtual double circumference() const {
    return 0.0;
  }

  virtual double area() const {
    return 0.0;
  }
};

} // end namespace figfit
