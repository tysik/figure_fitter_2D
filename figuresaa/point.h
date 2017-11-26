#pragma once

#include <cmath>
#include <stdexcept>

namespace figfit
{

class Point : public Figure
{
public:
  Point(double x = 0.0, double y = 0.0) :
    x_(x), y_(y)
  {}

  Point(const Point &p) :
    x_(p.x_), y_(p.y_)
  {}

  double x() const
  {
    return x_;
  }

  double y() const
  {
    return y_;
  }

  double squared_distance_to(const Point &p) const
  {
    return sqr(p.x() - x_) + sqr(p.y() - y_);
  }

  double distance_to(const Point &p) const
  {
    return sqrt(squared_distance_to(p));
  }

private:
  double x_;
  double y_;
};


std::ostream& operator<<(std::ostream &out, const Point &p)
{
  out << "(" << p.x() << ", " << p.y() << ")";
  return out;
}

}
