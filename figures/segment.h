#pragma once

#include "../figures/line.h"

namespace figfit
{

/**
 * @class Segment segment.h
 *
 * @brief The Segment class
 *
 * Segment is a figure created upon a supporting line. It can be described with
 * two points: start-point and end-point. The order of points does matter
 * because for the parametric representation of the segment it is assumed that
 * the parameter runs from the first point to the second point.
 */
class Segment : public Line
{
public:

  //
  // Constructors
  //

  virtual ~Segment() = default;

  Segment(const Segment& rhs) = default;
  Segment& operator=(const Segment& rhs) = default;

  Segment(Segment&& rhs) = default;
  Segment& operator=(Segment&& rhs) = default;

  /**
   * @brief Construction from two points (default)
   *
   * Note that default segment is constructed from points (0,0) and (1,0). The
   * order of provided points does matter.
   *
   * @param start is a start-point of the segment
   * @param start is a end-point of the segment
   *
   * @throw std::logic_error if p1 = p2
   */
  Segment(const Point& start = Point(), const Point& end = Point(1.0, 0.0)) :
    Line(start, end),
    start_point_(start),
    end_point_(end)
  {}

  //
  // Inherited methods
  //

  /**
   * @brief Compute normal vector from this segment to a given point
   *
   * If the projection of a given point onto the supporting line of this segment
   * falls "behind" its limits, normal to the closest end point is returned.
   */
  virtual Vec normalTo(const Point& p) const override {
    double t = parametricRepresentation(p);

    if (t < 0.0)
      return (p - start_point_).normalized();
    else if (t > 1.0)
      return (p - end_point_).normalized();
    else
      return Line::normalTo(p);
  }

  /**
   * @brief Compute squared distance from this segment to a given point
   *
   * If the projection of a given point onto the supporting line of this segment
   * falls "behind" its limits, squared distance to the closest end point is
   * returned.
   */
  virtual double distanceSquaredTo(const Point& p) const {
    double t = parametricRepresentation(p);

    if (t < 0.0)
      return (p - start_point_).lengthSquared();
    else if (t > 1.0)
      return (p - end_point_).lengthSquared();
    else
      return Line::distanceSquaredTo(p);
  }

  /**
   * @brief Compute distance from this segment to a given point
   *
   * If the projection of a given point onto the supporting line of this segment
   * falls "behind" its limits, distance to the closest end point is returned.
   */
  virtual double distanceTo(const Point& p) const {
    return sqrt(this->distanceSquaredTo(p));
  }

  /**
   * @brief Find projection of a given point onto this segment
   *
   * If the projection of a given point onto the supporting line of this segment
   * falls "behind" its limits, the closest end point is returned.
   */
  virtual Point findProjectionOf(const Point& p) const override {
    double t = this->parametricRepresentation(p);

    if (t < 0.0)
      return start_point_;
    else if (t > 1.0)
      return end_point_;
    else
      return Line::findProjectionOf(p);
  }

  //
  // Segment specific methods
  //

  /**
   * @brief Get parametric representation of a point
   *
   * Position along the segment can be parametrized by a single value t so that
   * when p coincides with the first point of the segment then t is equal to
   * zero and when p coincides with the second point of the segment then t is
   * equal to one. Parameter t can be less than zero or greater than 1 if the
   * projeciton of point onto the segment line falls behind its limits
   *
   * @param p is a given point; projection of p onto segment line is taken
   * for calculations of t
   *
   * @return parameter t
   *
   * @throw std::logic_error if length of this segment is zero
   */
  double parametricRepresentation(const Point& p) const {
    // TODO: Why throwing? In such case start = end -> return 0.0 - min(double)
    // or 1.0 + min(double);
    double length_squared = lengthSquared();
    if (length_squared == 0.0)
      throw std::logic_error("Could not find parametric representation for "
                             "zero-length segment");

    Vec a = end_point_ - start_point_;
    Vec b = p - start_point_;

    return a.dot(b) / length_squared;
  }

  /**
   * @brief Get squared length of this segment
   *
   * @return squared length of this segment
   */
  double lengthSquared() const {
    return (start_point_ - end_point_).lengthSquared();
  }

  /**
   * @brief Get length of this segment
   *
   * @return length of this segment
   */
  double length() const {
    return (start_point_ - end_point_).length();
  }

  /**
   * @brief Get first point
   *
   * @return first point
   */
  Point startPoint() const {
    return start_point_;
  }

  /**
   * @brief Get second point
   *
   * @return second point
   */
  Point endPoint() const {
    return end_point_;
  }

  //
  // Ostream operator
  //

  friend std::ostream& operator<<(std::ostream& out, const Segment& s) {
    out << "[" << s.start_point_ << ", " << s.end_point_ << "]";
    return out;
  }

private:

  Point start_point_;   /**< @brief Beginning of the segment */
  Point end_point_;     /**< @brief End of the segment */
};

} // end namespace figfit
