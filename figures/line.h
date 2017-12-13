#pragma once

#include <stdexcept>
#include <limits>

#include "figure.h"
#include "point.h"

namespace figfit
{

/**
  @class Line line.h

 * @brief The Line class
 *
 * Line is a Figure of infinite length. It is represented with general form as
 * Ax + By + C = 0, where A, B, C are coefficients. The coefficients are
 * normalized by factor sqrt(A^2 + B^2). A and B cannot both be zero. If so, the
 * methods of Line are ill-defined.
 */
class Line : public Figure
{
public:

  //
  // Constructors
  //

  virtual ~Line() = default;

  Line(const Line& rhs) = default;
  Line& operator=(const Line& rhs) = default;

  Line(Line&& rhs) = default;
  Line& operator=(Line&& rhs) = default;

  /**
   * @brief Construction from parameters (default)
   *
   * Constructs a line based on given general equation parameters. The
   * parameters are normalized during construction.
   *
   * @param A is A
   * @param B is B
   * @param C is C
   *
   * @throw std::logic_error if both A = 0 and B = 0
   */
  Line(double A = 1.0, double B = 0.0, double C = 0.0) :
    A_(A), B_(B), C_(C)
  {
    if (A == 0.0 && B == 0.0)
      throw std::logic_error("Cannot create line when both A = 0 and B = 0");

    normalizeCoefficients();
  }

  /**
   * @brief Construction from two points
   *
   * Constructs a line based on given two points laying on the line. Obtained
   * parameters of general equation are normalized.
   *
   * @param p1 is first point
   * @param p2 is second point
   *
   * @throw std::logic_error if p1 = p2
   */
  Line(const Point& p1, const Point& p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;

    if (dx == 0.0 && dy == 0.0)
      throw std::logic_error("Cannot calculate line parameters from two "
                             "identical points");

    if (dx != 0.0) {
      A_ = dy / dx;
      B_ = -1.0;
      C_ = p1.y - A_ * p1.x;
    }
    else {
      A_ = 1.0;
      B_ = 0.0;
      C_ = -p1.x;
    }

    normalizeCoefficients();
  }

  //
  // Inherited methods
  //

  /**
   * @brief Compute normal vector from this line to a given point
   */
  virtual Vec normalTo(const Point& p) const override {
    return (p - findProjectionOf(p)).normalized();
  }

  /**
   * @brief Compute squared distance from this line to a given point
   */
  virtual double distanceSquaredTo(const Point& p) const override {
    return (p - findProjectionOf(p)).lengthSquared();
  }

  /**
   * @brief Compute distance from this line to a given point
   */
  virtual double distanceTo(const Point& p) const override {
    return std::abs(A_ * p.x + B_ * p.y + C_);
  }

  /**
   * @brief Find projection of a given point onto this line
   */
  virtual Point findProjectionOf(const Point& p) const override {
    double x_coord = B_ * (B_ * p.x - A_ * p.y) - A_ * C_;
    double y_coord = A_ * (A_ * p.y - B_ * p.x) - B_ * C_;

    return Point(x_coord, y_coord);
  }

  //
  // Line specific methods
  //

  /**
   * @brief Find intersection with given line
   *
   * @param l is a given line
   *
   * @return point of intersection of this and given line
   *
   * @throw std::logic_error if lines are parallel
   */
  Point findIntersectionWith(const Line& l) const {
    double denominator = A_ * l.B_ - B_ * l.A_;

    if (denominator == 0.0)
      throw std::logic_error("Cannot find intersection: lines are parallel");

    return Point((B_ * l.C_ - C_ * l.B_) / denominator,
                 (C_ * l.A_ - A_ * l.C_) / denominator);
  }

  /**
   * @brief Check if given line is parallel to this
   *
   * @param l is a given line
   *
   * @return true if lines are parallel
   */
  bool isParallelTo(const Line& l) const {
    return (A_ * l.B_ - B_ * l.A_ == 0.0);
  }

  /**
   * @brief Check if given line is perpendicular to this
   *
   * @param l is a given line
   *
   * @return true if lines are perpendicular
   */
  bool isPerpendicularTo(const Line& l) const {
    return (A_ * l.A_ + B_ * l.B_ == 0.0);
  }

  /**
   * @brief Create point on the line given x coordinate
   *
   * @param x_coord is the coordinate on abscissa
   *
   * @return point (x_coord, y_coord) where y_coord is calculated
   *
   * @throw std::logic_error when the line is vertical
   */
  Point createPointFromX(double x_coord) const {
    if (B_ == 0.0)
      throw std::logic_error("Cannot create point from x coordinate on a "
                             "vertical line");

    return Point(x_coord, -(A_ * x_coord + C_) / B_);
  }

  /**
   * @brief Create point on the line given y coordinate
   *
   * @param y_coord is the coordinate on ordinate
   *
   * @return point (x_coord, y_coord) where x_coord is calculated
   *
   * @throw std::logic_error when the line is horizontal
   */
  Point createPointFromY(double y_coord) const {
    if (A_ == 0.0)
      throw std::logic_error("Cannot create point from y coordinate on a "
                             "horizontal line");

    return Point(-(B_ * y_coord + C_) / A_, y_coord);
  }

  /**
   * @brief Get A
   *
   * @return coefficient A
   */
  double A() const {
    return A_;
  }

  /**
   * @brief Get B
   *
   * @return coefficient B
   */
  double B() const {
    return B_;
  }

  /**
   * @brief Get C
   *
   * @return coefficient C
   */
  double C() const {
    return C_;
  }

  //
  // Ostream operator
  //

  friend std::ostream& operator<<(std::ostream& out, const Line& l) {
    out << "(" << l.A_ << ", " << l.B_ << ", " << l.C_ << ")";
    return out;
  }

protected:

  double A_;  /**< @brief Rate of change in abscissa */
  double B_;  /**< @brief Rate of change in ordinate */
  double C_;  /**< @brief Offset */

private:

  /**
   * @brief Normalize coefficients A, B, C
   *
   * @throw std::logic_error if both A = 0 and B = 0
   */
  void normalizeCoefficients() {
    double denominator = A_ * A_ + B_ * B_;
    if (denominator == 0.0)
      throw std::logic_error("Could not normalize line segment: "
                             "A^2 + B^2 == 0");

    double mu = (C_ <= 0.0) ?  1.0 / sqrt(denominator) :
                              -1.0 / sqrt(denominator);

    A_ *= mu;
    B_ *= mu;
    C_ *= mu;
  }
};

} // end namespace figfit
