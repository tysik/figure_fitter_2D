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

  Point(const Vec &v) :
    Vec(v)
  {}

  virtual Vec normalTo(const Point &p) const {
    return normalize(p - *this);
  }

  virtual double distanceSquaredTo(const Point &p) const {
    return (p - *this).lengthSquared();
  }

  virtual double distanceTo(const Point &p) const {
    return sqrt(distanceSquaredTo(p));
  }
};

} // end namespace figfit
