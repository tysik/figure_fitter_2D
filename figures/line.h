#pragma once

#include <stdexcept>
#include <limits>

#include "figure.h"
#include "point.h"

namespace figfit
{

class Line : public Figure
{
public:
  Line(double A = 1.0, double B = 0.0, double C = 0.0) :
    A_(A), B_(B), C_(C)
  {
    normalize();
  }

  Line(const Point &p1, const Point &p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;

    if (dx == 0.0 && dy == 0.0)
      throw std::logic_error("Cannot calculate line parameters from two "
                             "identical points");

    if (dx != 0.0) {
      A_ = dy / dx;
      B_ = -1.0;
      C_ = p1.y - A_ * p1.x;
    }
    else {
      A_ = 1.0;
      B_ = 0.0;
      C_ = -p1.x;
    }

    normalize();
  }

  Line(const Line &l) :
    A_(l.A_), B_(l.B_), C_(l.C_)
  {}

  virtual Vec normalTo(const Point &p) const {
    // TODO: find direction to point
    return Vec(A_, B_);
  }

  virtual double distanceSquaredTo(const Point &p) const {
    Point projected = findProjectionOf(p);
    return (p - projected).lengthSquared();
  }

  virtual double distanceTo(const Point &p) const {
    return std::abs(A_ * p.x + B_ * p.y + C_);
  }

  Point createPointFromX(double x_coord) const {
    if (B_ == 0.0)
      throw std::logic_error("Cannot create point on segment");

    return Point(x_coord, -(A_ * x_coord + C_) / B_);
  }

  Point createPointFromY(double y_coord) const {
    if (A_ == 0.0)
      throw std::logic_error("Cannot create point on segment");

    return Point(-(B_ * y_coord + C_) / A_, y_coord);
  }

  Point findProjectionOf(const Point &p) const {
    double x_coord = B_ * (B_ * p.x - A_ * p.y) - A_ * C_;
    double y_coord = A_ * (A_ * p.y - B_ * p.x) - B_ * C_;

    return Point(x_coord, y_coord);
  }

  Point findIntersectionWith(const Line &l) const {
    double denominator = A_ * l.B_ - B_ * l.A_;

    if (denominator == 0.0)
      throw std::logic_error("Cannot find intersection: lines are parallel");

    return Point((B_ * l.C_ - C_ * l.B_) / denominator,
                 (C_ * l.A_ - A_ * l.C_) / denominator);
  }

  bool isParallelTo(const Line &l) const {
    return (A_ * l.B_ - B_ * l.A_ == 0.0);
  }

  bool isPerpendicularTo(const Line &l) const {
    return (A_ * l.A_ + B_ * l.B_ == 0.0);
  }

  friend std::ostream& operator<<(std::ostream &out, const Line &l) {
    out << "(" << l.A_ << ", " << l.B_ << ", " << l.C_ << ")";
    return out;
  }

private:
  void normalize() {
    double denominator = A_ * A_ + B_ * B_;
    if (denominator == 0.0)
      throw std::logic_error("Could not normalize line segment: A^2 + B^2 == 0");

    double mu = (C_ <= 0.0) ? 1.0 / sqrt(denominator) : -1.0 / sqrt(denominator);

    A_ *= mu;
    B_ *= mu;
    C_ *= mu;
  }

  double A_, B_, C_;
};

} // end namespace figfit
