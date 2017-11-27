#pragma once

#include "vec.h"

namespace figfit
{

class Point;

class Figure
{
public:
  virtual Vec normalTo(const Point &p) const = 0;

  virtual double distanceSquaredTo(const Point &p) const = 0;

  virtual double distanceTo(const Point &p) const = 0;
};

} // end namespace figfit
