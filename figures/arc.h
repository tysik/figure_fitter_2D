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

  virtual ~Arc() = default;

  Arc(const Arc& rhs) = default;
  Arc& operator=(const Arc& rhs) = default;

  Arc(Arc&& rhs) = default;
  Arc& operator=(Arc&& rhs) = default;

  Arc(const Point& center, double radius, double start, double stop) :
    Circle(center, radius),
    start_(start),
    stop_(stop)
  { }

  /**
   * @brief Construction from three points (default)
   *
   * Note that the default values of points are p1 = (1,0), p2 = (0,1),
   * p3 = (sqrt(2)/2, sqrt(2)/2).
   *
   * @param p1 is the first point
   * @param p2 is the second point
   * @param paux is the auxiliary point for circle construction
   *
   * @throw std::logic_error if the points lay on the same line
   */
  Arc(const Point& p1,
      const Point& p2,
      const Point& p_aux):
    Circle(p1, p2, p_aux),
    first_point_(p1),
    second_point_(p2)
  {}

  //
  // Inherited methods
  //

  /**
   * @brief Compute normal vector from this arc to a given point
   */
  virtual Vec normalTo(const Point &p) const {
    return Circle::normalTo(p);
  }

  /**
   * @brief Compute squared distance from this circle to a given point
   */
  virtual double distanceSquaredTo(const Point &p) const {
    return Circle::distanceSquaredTo(p);
  }

  /**
   * @brief Compute distance from this circle to a given point
   */
  virtual double distanceTo(const Point &p) const {
    return Circle::distanceTo(p);
  }

  /**
   * @brief Find projection of a given point onto this circle
   *
   * @throw std::logic_error if a point coincides with the circle center
   */
  virtual Point findProjectionOf(const Point &p) const {
    return Circle::findProjectionOf(p);
  }

  // Hide these methods inherited from circle:
  bool isEncircling(const Point& p) const = delete;
  bool isEncircling(const Circle& c) const = delete;

  //
  // Arc specific methods
  //

  /**
   * @brief Get parametric representation of a point
   *
   * Position along the arc can be parametrized by a single value t so that
   * when p coincides with the first point of the arc then t is equal to
   * zero and when p coincides with the second point of the arc then t is
   * equal to one. Parameter t can be less than zero or greater than 1 if the
   * projeciton of point onto the arc circle falls behind its limits
   *
   * @param p is a given point; projection of p onto arc circle is taken
   * for calculations of t
   *
   * @return parameter t
   *
   * @throw std::logic_error if length of this arc is zero or the point is
   * located at the center of arc circle
   */
  double parametricRepresentation(const Point& p) const {
    double phi_1 = atan2(first_point_.y - center_.y,
                         first_point_.x - center_.x);
    double phi_2 = atan2(second_point_.y - center_.y,
                         second_point_.x - center_.x);

    double theta = phi_2 - phi_1;

    Point p_proj = Circle::findProjectionOf(p);
    double phi_p = atan2(p_proj.y - center_.y,
                         p_proj.x - center_.x);

    Vec a = second_point_ - first_point_;
    Vec b = p - first_point_;

//    double length_squared = this->lengthSquared();
//    if (length_squared == 0.0)
//      throw std::logic_error("Could not find parametric representation for "
//                             "zero-length segment");

    return 1;
  }


  /**
   * @brief Squared length of arc
   *
   * @return squared length of arc
   */
  double lengthSquared() const {
    return 0.0;
  }

  /**
   * @brief Length of arc
   *
   * @return length of arc
   */
  double length() const {
    double phi_1 = atan2(first_point_.y - center_.y,
                         first_point_.x - center_.x);
    double phi_2 = atan2(second_point_.y - center_.y,
                         second_point_.x - center_.x);
    double theta = phi_2 - phi_1;

    return radius_ * std::abs(theta) / (2.0 * M_PI);
  }

  /**
   * @brief Get first point
   *
   * @return first point
   */
  Vec firstPoint() const {
    return first_point_;
  }

  /**
   * @brief Get second point
   *
   * @return second point
   */
  Vec secondPoint() const {
    return second_point_;
  }

  //
  // Ostream operator
  //

  friend std::ostream& operator<<(std::ostream &out, const Arc &a) {
    out << "[" << a.center_ << ", " << a.radius_
        << a.first_point_   << ", " << a.second_point_ << "]";
    return out;
  }

private:

  Point first_point_;   /**< @brief First point of the arc */
  Point second_point_;  /**< @brief Second point of the arc */

  double start_;
  double stop_;
};

} // end namespace figfit
