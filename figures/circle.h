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

  /**
   * @brief Construction from three points
   *
   * The points cannot lay on the same line.
   *
   * @param p1 is the first point
   * @param p2 is the second point
   * @param p3 is the third point
   *
   * @throw std::logic_error if the points are located on the same line
   */
  Circle(const Point &p1, const Point &p2, const Point &p3) {
    double denominator = 2.0 * (p1.x * (p2.y - p3.y) -
                                p1.y * (p2.x - p3.x) +
                                p2.x * p3.y - p3.x * p2.y);

    if (denominator == 0.0)
      throw std::logic_error("Cannot create circle from three points lying on "
                             "the same line.");

    double x_coord = (p1.lengthSquared() * (p2.y - p3.y) +
                      p2.lengthSquared() * (p3.y - p1.y) +
                      p3.lengthSquared() * (p1.y - p2.y)) / denominator;

    double y_coord = (p1.lengthSquared() * (p3.x - p2.x) +
                      p2.lengthSquared() * (p1.x - p3.x) +
                      p3.lengthSquared() * (p2.x - p1.x)) / denominator;

    center_ = Point(x_coord, y_coord);
    radius_ = (p1 - center_).length();
  }

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
