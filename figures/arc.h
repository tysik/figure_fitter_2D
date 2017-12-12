#pragma once

#include "../figures/circle.h"

namespace figfit
{

/**
 * @class Arc arc.h
 *
 * @brief The Arc class
 *
 * Arc is a special case of non-closed circle and therefore is a figure. It is
 * defined by two points lying on the circle. Depending on the order of
 * providing points, the arc is defined to be a section of the circle or its
 * negation.
 */
class Arc : public Circle
{
public:

  //
  // Constructors
  //
  /**
   * @brief Construction from three points
   *
   * Note that default segment is constructed from points (0,0) and (1,0).
   *
   * @param p1 is the first point
   * @param p2 is the second point
   *
   * @throw std::logic_error if p1 = p2
   */
  Arc(const Point &p1 = Point(), const Point &p2 = Point(1.0, 0.0)):
    Circle(p1, 1),
    first_point_(p1),
    second_point_(p2)
  {}

  //
  // Inherited methods
  //
  virtual Vec normalTo(const Point &p) const {
    Vec a = second_point_ - first_point_;
    Vec b = p - first_point_;
    Vec c = p - second_point_;

    double t = a.dot(b) / a.lengthSquared();

    if (t < 0.0)
      return b.normalized();
    else if (t > 1.0)
      return c.normalized();
    else
      return normalize(p - findProjectionOf(p));
  }

  virtual double distanceSquaredTo(const Point &p) const {
    Vec a = second_point_ - first_point_;
    Vec b = p - first_point_;
    Vec c = p - second_point_;

    double t = a.dot(b) / a.lengthSquared();

    if (t < 0.0)
      return b.lengthSquared();
    else if (t > 1.0)
      return c.lengthSquared();
    else
      return Circle::distanceSquaredTo(p);
  }

  virtual double distanceTo(const Point &p) const {
    return sqrt(distanceSquaredTo(p));
  }

  virtual Point findProjectionOf(const Point &p) const {
    Vec a = second_point_ - first_point_;
    Vec b = p - first_point_;
    Vec c = p - second_point_;

    double t = a.dot(b) / a.lengthSquared();

    if (t < 0.0)
      return first_point_.findProjectionOf(p);
    else if (t > 1.0)
      return second_point_.findProjectionOf(p);
    else
      return Circle::findProjectionOf(p);
  }

  //
  // Segment specific methods
  //
  /**
   * @brief Length of segment
   * @return length of segment
   */
  double length() const {
    return (first_point_ - second_point_).length();
  }

  //
  // Getter methods
  //
  /**
   * @brief Get first point
   * @return first point
   */
  Vec firstPoint() const {
    return first_point_;
  }

  /**
   * @brief Get second point
   * @return second point
   */
  Vec secondPoint() const {
    return second_point_;
  }

  //
  // Ostream operator
  //
  friend std::ostream& operator<<(std::ostream &out, const Arc &a) {
    out << "[" << a.first_point_ << ", " << a.second_point_ << "]";
    return out;
  }

private:
  Point first_point_;   /**< @brief First point of the segment */
  Point second_point_;  /**< @brief Second point of the segment */
};

} // end namespace figfit