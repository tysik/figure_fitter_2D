#pragma once

#include "../figures/line.h"

namespace figfit
{

class Segment : public Line
{
public:
  Segment() :
    Line(1.0, 0.0, 0.0)
  {}

  Segment(const Point &p1, const Point &p2):
    Line(p1, p2),
    first_point_(p1),
    second_point_(p2)
  {}

  /*
   * If the point's projection on segment lays outside
   * the normal is obtained from the edge point.
   */
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

  /*
   * The function projects point onto the line supporting
   * the segment and checks if its projection falls on the
   * segment or not. In the first case the distance between
   * point and segment is computed. In the latter case the
   * distance between point and one of the edge points is
   * computed. Projected point is obtained from equation:
   * p = p1 + t * (p2 - p1)
   */

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

  double length() const {
    return (first_point_ - second_point_).length();
  }

  Vec first_point() const {
    return first_point_;
  }

  Vec second_point() const {
    return second_point_;
  }

  friend std::ostream& operator<<(std::ostream &out, const Segment &s) {
    out << "[" << s.first_point_ << ", " << s.second_point_ << "]";
    return out;
  }

private:
  Vec first_point_;
  Vec second_point_;
};

} // end namespace figfit
