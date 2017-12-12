#pragma once

#include "vec.h"

namespace figfit
{

class Point;

/**
 * @class Figure figure.h
 *
 * @brief Base and interface class for all of figures
 *
 * Provides interface for most common functionalities of figures.
 */
class Figure
{
public:

  Figure() = default;
  virtual ~Figure() = default;

  Figure(const Figure& rhs) = default;
  Figure& operator=(const Figure& rhs) = default;

  Figure(Figure&& rhs) = default;
  Figure& operator=(Figure&& rhs) = default;

  /**
   * @brief Compute normal vector
   *
   * Computes normal vector pointing from the figure towards a given point. The
   * normal vector is perpendicular to the surface of the figure.
   *
   * @param p is a given point
   *
   * @returns normal vector
   *
   * @throw std::logic_error if a given point lays on the figure
   */
  virtual Vec normalTo(const Point& p) const = 0;

  /**
   * @brief Compute squared distance to point
   *
   * Computes square of minimal distance between given point and this figure.
   * This method is assumed to be computationally cheaper than distanceTo().
   *
   * @param p is a point to which the distance is computed
   *
   * @returns squared minimal distance to point
   *
   * @sa distanceTo()
   */
  virtual double distanceSquaredTo(const Point& p) const = 0;

  /**
   * @brief Compute distance to point
   *
   * Computes minimal distance between given point p and this figure. This
   * method is assumed to be computationally more expensive than
   * distanceSquaredTo().
   *
   * @param p is a point to which the distance is computed
   *
   * @returns minimal distance to point
   *
   * @sa distanceSquaredTo()
   */
  virtual double distanceTo(const Point& p) const = 0;

  /**
   * @brief Find projection of given point onto the figure
   *
   * @param p is a given point
   *
   * @return point on the figure that is nearest to the given point
   */
  virtual Point findProjectionOf(const Point& p) const = 0;
};

} // end namespace figfit
