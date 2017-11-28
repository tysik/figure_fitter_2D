#pragma once

#include <armadillo>
#include <vector>
#include <stdexcept>

#include "../figures/point.h"
#include "../figures/line.h"
#include "../figures/segment.h"

namespace figfit
{

class Fitter
{
public:
  explicit Fitter(const std::vector<Point> &points) :
    N_(points.size()),
    x_coords_(points.size()),
    y_coords_(points.size())
  {
    for (size_t i = 0; i < N_; ++i) {
      x_coords_(i) = points[i].x;
      y_coords_(i) = points[i].y;
    }
  }

  void fitPoint(Point &p);
  void fitPoint(Point &p, double &variance);

  void fitLine(Line &l);
  void fitLine(Line &l, double &variance);

  void fitSegment(Segment &s);
  void fitSegment(Segment &s, double &variance);

//  void fitCircle(Circle &circle, double &variance);
//  void fitArc(Arc &arc, double &variance);

private:
  size_t N_;
  arma::vec x_coords_;
  arma::vec y_coords_;
};


void Fitter::fitPoint(Point &p) {
  if (N_ < 1)
    throw std::logic_error("Error while fitting point. There must be at least"
                             " one point in the set.");

  double mean_x = mean(x_coords_);
  double mean_y = mean(y_coords_);

  p = Point(mean_x, mean_y);
}

void Fitter::fitPoint(Point &p, double &variance) {
  fitPoint(p);

  double var = 0.0;
  for (size_t i = 0; i < N_; ++i)
    var += p.distanceSquaredTo(Point(x_coords_(i), y_coords_(i)));
  variance = var / N_;
}

//
// WARNING: Badly fits lines through 0,0!
//
void Fitter::fitLine(Line &l) {
  if (N_ < 2)
    throw std::logic_error("Error while fitting line. There must be at least "
                             "two points in the set.");

  arma::mat input  = arma::mat(N_, 2).zeros();  // [x_i, y_i]
  arma::vec output = arma::vec(N_).ones();      // [-C]
  arma::vec params = arma::vec(2).zeros();      // [A ; B]

  input.col(0) = x_coords_;
  input.col(1) = y_coords_;

  params = arma::pinv(input) * output;

  if (params(0) == 0 && params(1) == 0)
    throw std::runtime_error("Error while fitting line");

  l = Line(params(0), params(1), -1.0);
}

void Fitter::fitLine(Line &l, double &variance) {
  fitLine(l);

  double var = 0.0;
  for (size_t i = 0; i < N_; ++i)
    var += l.distanceSquaredTo(Point(x_coords_(i), y_coords_(i)));
  variance = var / N_;
}


void Fitter::fitSegment(Segment &s) {
  Line line;
  fitLine(line);

  Point first_point(x_coords_(0), y_coords_(0));
  Point second_point(x_coords_(N_ - 1), y_coords_(N_ - 1));

  first_point = line.findProjectionOf(first_point);
  second_point = line.findProjectionOf(second_point);

  s = Segment(first_point, second_point);
}

void Fitter::fitSegment(Segment &s, double &variance) {
  Line line;
  fitLine(line, variance);

  Point first_point(x_coords_(0), y_coords_(0));
  Point second_point(x_coords_(N_ - 1), y_coords_(N_ - 1));

  first_point = line.findProjectionOf(first_point);
  second_point = line.findProjectionOf(second_point);

  s = Segment(first_point, second_point);
}


///**
// * Returns a total best fit approximation of
// * a circle based on given point set. The equation
// * used for fitting is given by
// *   a1 * x + a2 * y + a3 = x^2 + y^2
// * where parameters a1, a2, a3 are obtained from
// * circle equation
// *   (x-x0)^2 + (y-y0)^2 = r^2.
// **/
//Circle Fitter::fitCircle()
//{
//  if (N_ < 3)
//    throw std::runtime_error("Error while fitting circle. There must be at least three points in the set.");

//  arma::mat input  = arma::mat(N_, 3).zeros();   // [x_i, y_i, 1]
//  arma::vec output = arma::vec(N_).zeros();      // [-(x_i^2 + y_i^2)]
//  arma::vec params = arma::vec(3).zeros();      // [a_1 ; a_2 ; a_3]

//  for (size_t i = 0; i < N_; ++i)
//  {
//    input(i, 0) = points_[i].x;
//    input(i, 1) = points_[i].y;
//    input(i, 2) = 1.0;

//    output(i) = ( sqr(points_[i].x) + sqr(points_[i].y) ) / 2.0;
//  }

//  try
//  {
//    params = arma::pinv(input) * output;
//  }
//  catch (const std::exception &e)
//  {
//    throw std::runtime_error(e.what());
//  }

//  Point center(params(0), params(1));
//  double radius =  sqrt(sqr(params(0)) + sqr(params(1)) + 2.0 * params(2));

//  return Circle(radius, center);
//}

} // end namespace figfit
