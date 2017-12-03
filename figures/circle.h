#pragma once

#include "figure.h"
#include "point.h"

namespace figfit {

/**
 * @class Circle circle.h
 *
 * @brief The Circle class
 *
 * The circle is a Figure represented by a central point and a radius. The
 * radius is assumed to be positive. If radius is <= 0 the methods of circle
 * are ill-defined.
 */
class Circle : public Figure
{ 
public:

  //
  // Constructors
  //
  /**
   * @brief Construction from point and radius
   *
   * Provided radius must be greater than zero. Constructor does not check if
   * this is true. Default radius is 1.
   *
   * @param center is the central point of the circle
   * @param radius is the radius of the circle
   */
  Circle(const Point &center = Point(), double radius = 1.0) :
    center_(center),
    radius_(radius)
  { }

  //
  // Inherited methods
  //
  virtual Vec normalTo(const Point &p) const {
    return normalize(p - center_);
  }

  virtual double distanceSquaredTo(const Point &p) const {
    return fabs((p - center_).lengthSquared() - pow(radius_, 2.0));
  }

  virtual double distanceTo(const Point &p) const {
    return fabs((p - center_).length() - radius_);
  }

  virtual Point findProjectionOf(const Point &p) const {
    return radius_ * (p - center_).normalized() + center_;
  }

  //
  // Circle specific methods
  //
  /**
   * @brief Check if given point is inside this circle
   *
   * Point lying on the circumference of the circle is assumed to be encircled
   * by it.
   *
   * @param p is the given point
   * @return true if p is inside this circle
   */
  bool isEncircling(const Point &p) {
    return pow(radius_, 2.0) >= (p - center_).lengthSquared();
  }

  /**
   * @brief Check if given circle is inside this circle
   *
   * Circle tangent to another circle from inside of it is assumed to be
   * encircled by it.
   *
   * @param c is the given circle
   * @return true if c is inside this circle
   */
  bool isEncircling(const Circle &c) {
    return radius_ >= (c.center_ - center_).length() + c.radius_;
  }

  //
  // Getter methods
  //
  /**
   * @brief Get center
   * @return central point of the circle
   */
  Point center() const {
    return center_;
  }

  /**
   * @brief Get radius
   * @return radius of the circle
   */
  double radius() const {
    return radius_;
  }

  //
  // Ostream operator
  //
  friend std::ostream& operator<<(std::ostream &out, const Circle &c) {
    out << "[" << c.center_ << ", " << c.radius_ << "]";
    return out;
  }

protected:

  Point center_;    /**< @brief Central point of the circle */
  double radius_;   /**< @brief Radius of the circle */
};

} // end namespace figfit
