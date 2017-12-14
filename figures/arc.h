#pragma once

#include "../figures/circle.h"

namespace figfit
{

/**
 * @class Arc arc.h
 *
 * @brief The Arc class
 *
 * Arc is a figure created upon a supporting circle. It is defined by two points
 * laying on this circle, which can be represented in a parametric form by
 * angles start and stop.
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

  /**
   * @brief Construction from center, radius and start/stop angles (default)
   *
   * The arc is created upon circle of center and radius. It is spread from
   * angle start to angle stop in a counter-clokwise manner. The angles are
   * provided in radians in range [-pi;pi].
   *
   * Note that the default values of center is (0,0), radius is 1, start angle
   * is 0 rad and stop angle is 1 rad.
   *
   * @param center is a center point of the supporting circle
   * @param radius is a radius of the supporting circle
   * @param start is a start-point angle in radians
   * @param stop is an end-point angle in radians
   */
  Arc(const Point& center = Point(), double radius = 1.0,
      double start = 0.0, double stop = 1.0) :
    Circle(center, radius),
    start_(atan2(sin(start), cos(start))),
    end_(atan2(sin(stop), cos(stop)))
  {
    start_point_ = center + radius_ * Point(cos(start), sin(start));
    end_point_ = center + radius_ * Point(cos(stop), sin(stop));
  }

  /**
   * @brief Construction from three points
   *
   * @param start is a start-point of the arc
   * @param stop is an end-point of the arc
   * @param paux is an auxiliary point for construction of supporting circle
   *
   * @throw std::logic_error if the points lay on the same line
   */
  Arc(const Point& start,
      const Point& stop,
      const Point& aux):
    Circle(start, stop, aux),
    start_point_(start),
    end_point_(stop)
  {
    start_ = atan2(start.y - center_.y, start.x - center_.x);
    end_ = atan2(stop.y - center_.y, stop.x - center_.x);
  }

  //
  // Inherited methods
  //

  /**
   * @brief Compute normal vector from this arc to a given point
   */
  virtual Vec normalTo(const Point &p) const override {
    return Circle::normalTo(p);
  }

  /**
   * @brief Compute squared distance from this circle to a given point
   */
  virtual double distanceSquaredTo(const Point &p) const override {
    return Circle::distanceSquaredTo(p);
  }

  /**
   * @brief Compute distance from this circle to a given point
   */
  virtual double distanceTo(const Point &p) const override {
    return Circle::distanceTo(p);
  }

  /**
   * @brief Find projection of a given point onto this circle
   *
   * @throw std::logic_error if a point coincides with the circle center
   */
  virtual Point findProjectionOf(const Point &p) const override {
    Vec v_m = this->midPoint() - center_;
    Vec v1 = start_point_ - center_;
    Vec v2 = end_point_ - center_;
    Vec v = p - center_;

    double s_m = v_m.cross(v);
    double s1 = v1.cross(v);
    double s2 = v2.cross(v);
    double s = v1.cross(v2);

    if (s >= 0.0) {
      // Arc is less than half of circle perimeter
      if (s1 > 0.0 && s2 < 0.0)
        return Circle::findProjectionOf(p);
      else if (s_m <= 0.0)
        return start_point_;
      else
        return end_point_;
    }
    else {
      // Arc is more than half of circle perimeter
      if (s1 > 0.0 || s2 < 0.0)
        return Circle::findProjectionOf(p);
      else if (s_m >= 0.0)
        start_point_;
      else
        end_point_;
    }

    return p;
  }

  // Hide these methods inherited from circle:
  bool isEncircling(const Point& p) const = delete;
  bool isEncircling(const Circle& c) const = delete;

  //
  // Arc specific methods
  //

  /**
   * @brief Get parametric representation of a point on this arc
   *
   * Position along the arc can be parametrized by a single value theta so that
   * when p coincides with the start-point of the arc then theta is equal to
   * zero and when p coincides with the end-point of the arc then theta is
   * equal to one. Parameter theta can be less than zero or greater than 1 if
   * the projeciton of point onto the supporting circle falls behind arcs
   * limits.
   *
   * @param p is a given point; projection of p onto supporting circle is taken
   * for calculations of theta
   *
   * @return parameter theta
   *
   * @throw std::logic_error if point p is located at the center of arc circle
   */
  double parametricRepresentation(const Point& p) const {
    double length = this->length();
    if (length == 0.0)
      throw std::logic_error("Could not find parametric representation for "
                             "zero-length arc");

    Point p_proj = Circle::findProjectionOf(p);
    double phi = atan2(p_proj.y - center_.y, p_proj.x - center_.x);

    double a = end_ - start_;
    double b = phi - start_;

    double midway = (a >= 0.0 ? a : a + M_PI) / 2.0;
    double opposite_midway = atan2(sin(M_PI + midway), cos(M_PI + midway));

    if (a >= 0.0)
      return b / a;
    else
      return b / (a + M_PI);

    return 1;
  }


//  double parametricRepresentation(double phi) const {
//    double midway = (a >= 0.0 ? a : a + M_PI) / 2.0;
//    double opposite_midway = atan2(sin(M_PI + midway), cos(M_PI + midway));


//    double a = end_ - start_;
//    double b = phi - start_;


//    if (a >= 0.0)
//      return b / a;
//    else
//      return b / (a + M_PI);

//    return 1;
//  }


  /**
   * @brief Get squared length of this arc
   *
   * Note that calculating length of arc is faster than calculating its length
   * squared.
   *
   * @return squared length of this arc
   */
  double lengthSquared() const {
    return pow(length(), 2.0);
  }

  /**
   * @brief Get length of this arc
   *
   * @return length of this arc
   */
  double length() const {
    double angle = end_ - start_;
    return radius_ * (angle >= 0.0 ? angle : angle + 2.0 * M_PI);
  }

  /**
   * @brief Get start-point angle of this arc
   *
   * @return start-point angle of this arc
   */
  double startAngle() const {
    return start_;
  }

  /**
   * @brief Get end-point angle of this arc
   *
   * @return end-point angle of this arc
   */
  double endAngle() const {
    return end_;
  }

  /**
   * @brief Get start-point of this arc
   *
   * @return start-point of this arc
   */
  Point startPoint() const {
    //return center_ + radius_ * Point(cos(start_), sin(start_));
    return start_point_;
  }

  /**
   * @brief Get end-point of this arc
   *
   * @return end-point of this arc
   */
  Point endPoint() const {
    //return center_ + radius_ * Point(cos(start_), sin(start_));
    return end_point_;
  }

  /**
   * @brief Get middle-point of this arc
   *
   * @return middle-point of this arc
   */
  Point midPoint() const {
    Vec v1 = start_point_ - center_;
    Vec v2 = end_point_ - center_;

    // If v1 = -v2 the simply return p1 on circle rotated by 90 deg.
    if ((v1 + v2).lengthSquared() == 0.0)
      return center_ + v2.rotate90();

    double sign = v1.cross(v2) >= 0.0 ? 1.0 : -1.0;

    return center_ + sign * radius_ * (v1 + v2).normalized();
  }

  //
  // Ostream operator
  //

  friend std::ostream& operator<<(std::ostream &out, const Arc &a) {
    out << "[" << a.center_ << ", " << a.radius_ << ", "
        << "{" << a.start_ << ", " << a.end_ << "}]";
    return out;
  }

private:

  // TODO: find out if the point-representation is better
  Point start_point_;
  Point end_point_;

  double start_;   /**< @brief Start-point angle */
  double end_;     /**< @brief End-point angle */
};

} // end namespace figfit
