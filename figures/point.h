#pragma once

#include "figure.h"

namespace figfit
{

/**
 * @class Point point.h
 *
 * @brief The Point class
 *
 * Point is a Figure and is a Vec(tor). It inherits the operation available for
 * vectors and also Point - Point = Vec.
 */
class Point : public Figure, public Vec
{
public:

  //
  // Constructors
  //
  /**
   * @brief Construction from coordinates
   *
   * @param x is abscissa coordinate
   * @param y is ordinate coordinate
   */
  Point(double x = 0.0, double y = 0.0) :
    Vec(x, y)
  {}

  /**
   * @brief Construction from vector
   * @param v is vector
   */
  Point(const Vec &v) :
    Vec(v)
  {}

  //
  // Inherited methods
  //
  virtual Vec normalTo(const Point &p) const {
    return normalize(p - *this);
  }

  virtual double distanceSquaredTo(const Point &p) const {
    return (p - *this).lengthSquared();
  }

  virtual double distanceTo(const Point &p) const {
    return sqrt(distanceSquaredTo(p));
  }

  virtual Point findProjectionOf(const Point &p) const {
    return *this;
  }
};

} // end namespace figfit
