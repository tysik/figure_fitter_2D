#pragma once

#include "../figures/line.h"

namespace figfit
{

/**
 * @class Segment segment.h
 *
 * @brief The Segment class
 *
 * Segment is a special case of finite Line and therefore is a Figure. It is
 * defined by general equation of line (Ax + By + C = 0) and two extreme points.
 */
class Segment : public Line
{
public:

  //
  // Constructors
  //
  /**
   * @brief Construction from two points
   *
   * Note that default segment is constructed from points (0,0) and (1,0).
   *
   * @param p1 is the first point
   * @param p2 is the second point
   *
   * @throw std::logic_error if p1 = p2
   */
  Segment(const Point &p1 = Point(), const Point &p2 = Point(1.0, 0.0)):
    Line(p1, p2),
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
      return Line::distanceSquaredTo(p);
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
      return Line::findProjectionOf(p);
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
  friend std::ostream& operator<<(std::ostream &out, const Segment &s) {
    out << "[" << s.first_point_ << ", " << s.second_point_ << "]";
    return out;
  }

private:
  Point first_point_;   /**< @brief First point of the segment */
  Point second_point_;  /**< @brief Second point of the segment */
};

} // end namespace figfit
