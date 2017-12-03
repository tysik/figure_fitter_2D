#pragma once

#include <armadillo>
#include <vector>
#include <stdexcept>

#include "../figures/point.h"
#include "../figures/line.h"
#include "../figures/segment.h"
#include "../figures/circle.h"
#include "../figures/arc.h"

/*! \mainpage Figure Fitters 2D
 *
 * figfit::Figure
 *
 * figfit::FigureFitter
 */

namespace figfit
{

/** \class FigureFitter figure_fitter.h
 * \brief Class containing general fitting functionalities
 *
 * The class acts as a container for the point set, from which figures such as
 * point, line, line segment, circle or arc can be fitted.
 *
 * The class exploits Armadillo library for matrix operations and can throw any
 * of its exceptions (cf. www.arma.sourceforge.net).
*/
class FigureFitter
{
public:

  //
  // Constructors
  //
  /** \brief Constructor with given point set
   *
   * Copies x and y coordinates of the given point set into appropriate
   * arma::vec objects and sets the size of the sample.
   *
   * \param points is the vector containing figfig::Point objects
  */
  FigureFitter(const std::vector<Point> &points) :
    N_(points.size()),
    x_coords_(points.size()),
    y_coords_(points.size())
  {
    for (size_t i = 0; i < N_; ++i) {
      x_coords_(i) = points[i].x;
      y_coords_(i) = points[i].y;
    }
  }

  //
  // Fitting methods
  //
  /**
   * @brief Fit point from the point set
   *
   * Computes the mean values of x and y coordinates and uses them to create
   * the resulting point.
   *
   * @param p is a placeholder for the resulting point
   */
  void fitPoint(Point &p);

  /**
   * @brief Fit point from the point set and get variance
   *
   * Performs the point fitting with fitPoint() method and then calculates the
   * variance of sample points around obtained figure.
   *
   * @param p is a placeholder for the resulting point
   * @param variance is a placeholder for the resulting variance
   */
  void fitPoint(Point &p, double &variance);

  /**
   * @brief Fit line from the point set
   *
   * Uses linear regression with the general line model Ax + By + C = 0. C is
   * set to -1 and A, B are the result of [A B] = pinv([x y]) * [C]. Here
   * pinv() is the Moore - Penrose pseudo inverse, [x y] and [C] denote matrix
   * and vector with N rows (N being the sample size).
   *
   * Note that this method is inappropriate for fitting lines crossing point
   * (0,0) (in such case C = 0).
   *
   * @param l is a placeholder for the resulting line
   */
  void fitLine(Line &l);

  /**
   * @brief Fit line from the point set and get variance
   *
   * Performs the line fitting with fitLine() method and then calculates the
   * variance of points around obtained figure.
   *
   * @param l is a placeholder for the resulting line
   * @param variance is a placeholder for the resulting variance
   */
  void fitLine(Line &l, double &variance);

  /**
   * @brief Fit segment from the point set
   *
   * Performs the line fitting with fitLine() method and projects the first and
   * last points of the set onto this line in order to obtain the segment.
   *
   * @param s is a placeholder for the resulting segment
   */
  void fitSegment(Segment &s);

  /**
   * @brief Fit segment from the point set and get variance
   *
   * Performs the segment fitting with fitSegment() method and then calculates
   * the variance of points around obtained figure.
   *
   * @param s is a placeholder for the resulting segment
   * @param variance is a placeholder for the resulting variance
   */
  void fitSegment(Segment &s, double &variance);

  /**
   * @brief Fit circle from the point set
   *
   * Uses linear regression to compute the parameters (center point and radius)
   * of the circle. The general circle equation (x - x0)^2 + (y - y0)^2 = r^2 is
   * turned into a1 * x + a2 * y + a3 = (x^2 + y^2) / 2, where a1 = x0, a2 = y0
   * and a3 = -(x0^2 + y0^2 - r^2) / 2. With such form the parameters can be
   * obtained from [a1 a2 a3] = pinv([x y 1]) * [x^2 + y^2] / 2
   *
   * @param c is a placeholder for the resulting circle
   */
  void fitCircle(Circle &c);

  /**
   * @brief Fit circle from the point set and get variance
   *
   * Performs the circle fitting with fitCircle() method and then calculates
   * the variance of points around obtained figure.
   *
   * @param s is a placeholder for the resulting circle
   * @param variance is a placeholder for the resulting variance
   */
  void fitCircle(Circle &c, double &variance);

  //  void fitArc(Arc &arc);
  //  void fitArc(Arc &arc, double &variance);

  //
  // Getter methods
  //
  /**
   * @brief Get x coordinates
   * @return vector of x coordinates of the point set
   */
  const arma::vec& xCoords() const {
    return x_coords_;
  }

  /**
   * @brief Get y coordinates
   * @return vector of y coordinates of the point set
   */
  const arma::vec& yCoords() const {
    return y_coords_;
  }

private:

  /**
   * @brief Find variance of points about given figure
   *
   * Computes sum of squared distances between sample points and the figure and
   * returns that value divided by number of samples.
   *
   * @param f is the given figure
   *
   * @return variance of sample points about figure
   */
  double findVarianceAbout(const Figure &f) const {
    double var = 0.0;
    for (size_t i = 0; i < N_; ++i)
      var += f.distanceSquaredTo(Point(x_coords_(i), y_coords_(i)));

    return var / N_;
  }

  size_t N_;            /**< Number of point (sample size) */
  arma::vec x_coords_;  /**< Vector containing x coordinates of points */
  arma::vec y_coords_;  /**< Vector containing y coordinates of points */
};


void FigureFitter::fitPoint(Point &p) {
  if (N_ < 1)
    throw std::logic_error("Error while fitting point. There must be at least "
                           "one point in the set.");

  double mean_x = mean(x_coords_);
  double mean_y = mean(y_coords_);

  p = Point(mean_x, mean_y);
}

void FigureFitter::fitPoint(Point &p, double &variance) {
  fitPoint(p);
  variance = findVarianceAbout(p);
}

void FigureFitter::fitLine(Line &l) {
  if (N_ < 2)
    throw std::logic_error("Error while fitting line. There must be at least "
                           "two points in the set.");

  arma::mat input  = arma::mat(N_, 2);      // [x_i, y_i]
  arma::vec output = arma::vec(N_).ones();  // [-C]
  arma::vec params = arma::vec(2);          // [A ; B]

  input.col(0) = x_coords_;
  input.col(1) = y_coords_;

  params = arma::pinv(input) * output;

  if (params(0) == 0 && params(1) == 0)
    throw std::runtime_error("Error while fitting line");

  l = Line(params(0), params(1), -1.0);
}

void FigureFitter::fitLine(Line &l, double &variance) {
  fitLine(l);
  variance = findVarianceAbout(l);
}

void FigureFitter::fitSegment(Segment &s) {
  Line line;
  fitLine(line);

  Point first_point(x_coords_(0), y_coords_(0));
  Point second_point(x_coords_(N_ - 1), y_coords_(N_ - 1));

  first_point = line.findProjectionOf(first_point);
  second_point = line.findProjectionOf(second_point);

  s = Segment(first_point, second_point);
}

void FigureFitter::fitSegment(Segment &s, double &variance) {
  fitSegment(s);
  variance = findVarianceAbout(s);
}

void FigureFitter::fitCircle(Circle &c) {
  if (N_ < 3)
    throw std::runtime_error("Error while fitting circle. There must be at "
                             "least three points in the set.");

  arma::mat input  = arma::mat(N_, 3);   // [x_i, y_i, 1]
  arma::vec output = arma::vec(N_);      // [(x_i^2 + y_i^2) / 2.0]
  arma::vec params = arma::vec(3);       // [a_1 ; a_2 ; a_3]

  input.col(0) = x_coords_;
  input.col(1) = y_coords_;
  input.col(2) = arma::vec(N_).ones();

  output = (arma::square(x_coords_) + arma::square(y_coords_)) / 2.0;

  params = arma::pinv(input) * output;

  Point center(params(0), params(1));
  double radius = sqrt(pow(params(0), 2.0) + pow(params(1), 2.0) + 2.0 * params(2));

  c = Circle(center, radius);
}

void FigureFitter::fitCircle(Circle &c, double &variance) {
  fitCircle(c);
  variance = findVarianceAbout(c);
}

} // end namespace figfit
