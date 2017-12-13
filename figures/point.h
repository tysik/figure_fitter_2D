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

  virtual ~Point() = default;

  Point(const Point& rhs) = default;
  Point& operator=(const Point& rhs) = default;

  Point(Point&& rhs) = default;
  Point& operator=(Point&& rhs) = default;

  /**
   * @brief Construction from coordinates (default)
   *
   * @param x is abscissa coordinate
   * @param y is ordinate coordinate
   */
  Point(double x = 0.0, double y = 0.0) :
    Vec(x, y)
  {}

  /**
   * @brief Construction from vector
   *
   * @param v is a vector
   */
  Point(const Vec& v) :
    Vec(v)
  {}

  //
  // Inherited methods
  //

  /**
   * @brief Compute normal vector from this point to a given point
   */
  virtual Vec normalTo(const Point& p) const override {
    return (p - *this).normalized();
  }

  /**
   * @brief Compute squared distance from this point to a given point
   */
  virtual double distanceSquaredTo(const Point& p) const override {
    return (p - *this).lengthSquared();
  }

  /**
   * @brief Compute distance from this point to a given point
   */
  virtual double distanceTo(const Point& p) const override {
    return (p - *this).length();
  }

  /**
   * @brief Find projection of a given point onto this point
   */
  virtual Point findProjectionOf(const Point& p) const override {
    return *this;
  }
};

} // end namespace figfit
