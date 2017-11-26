#pragma once

#include <cmath>
#include <stdexcept>

namespace figfit
{

inline double sqr(double x) { return x * x; }


class Figure
{};


class Point : public Figure
{
public:
  Point(double x = 0.0, double y = 0.0) :
    x_(x), y_(y)
  {}

  Point(const Point &p) :
    x_(p.x_), y_(p.y_)
  {}

  double x() const
  {
    return x_;
  }

  double y() const
  {
    return y_;
  }

  double squared_distance_to(const Point &p) const
  {
    return sqr(p.x() - x_) + sqr(p.y() - y_);
  }

  double distance_to(const Point &p) const
  {
    return sqrt(squared_distance_to(p));
  }

private:
  double x_;
  double y_;
};


class Line : public Figure
{
public:
  Line(double A = 1.0, double B = 0.0, double C = 0.0) : A_(A), B_(B), C_(C)
  {
    normalize_coefficients();
  }

  Line(const Point &p1, const Point &p2)
  {
    double dx = p2.x() - p1.x();
    double dy = p2.y() - p1.y();

    if (dx == 0.0 && dy == 0.0)
      throw std::logic_error("Cannot calculate line parameters from two "
                             "identical points");

    if (dx != 0.0)
    {
      A_ = dy / dx;
      B_ = -1.0;
      C_ = p1.y() - A_ * p1.x();
    }
    else
    {
      A_ = 1.0;
      B_ = 0.0;
      C_ = -p1.x();
    }

    normalize_coefficients();
  }

  Line(const Line &l) :
    A_(l.A_), B_(l.B_), C_(l.C_)
  {}

  double A() const
  {
    return A_;
  }

  double B() const
  {
    return B_;
  }

  double C() const
  {
    return C_;
  }

  double squared_distance_to(const Point &p)
  {
    return 0.0;
  }

  bool is_parallel(const Line &l)
  {
    return (A_ * l.B_ - B_ * l.A_ == 0.0);
  }

  bool is_perpendicular(const Line &l)
  {
    return (A_ * l.A_ + B_ * l.B_ == 0.0);
  }

private:
  void normalize_coefficients()
  {
    double denominator = sqrt(sqr(A_) + sqr(B_));
    if (denominator == 0.0)
      throw std::logic_error("Could not normalize line segment: sqr(A) + sqr(B) == 0");

    double mu = (C_ >= 0.0) ? (1.0 / denominator) : (-1.0 / denominator);
    A_ *= mu;
    B_ *= mu;
    C_ *= mu;
  }

  double A_, B_, C_;
};


class Segment : public Line
{
public:
  Segment(const Point &p1, const Point &p2) :
    Line(p1, p2), first_(p1), last_(p2) {}

  const Point& first_point() const { return first_; }
  const Point& last_point() const { return last_; }

private:
  Point first_;
  Point last_;
};


class Circle : public Figure
{
public:
  Circle() : radius(0.0), center(Point()) {}
  Circle(double r, double x, double y) : radius(r), center(Point(x, y)) {}
  Circle(double r, const Point &p) : radius(r), center(p) {}

  double radius;
  Point center;
};

class Arc : public Circle
{
public:
  Arc() {}

  double angle_min;
  double angle_max;
};


//class Box : public Figure
//{
//public:
//  Box() {}

//  Segment N, E, S, W;
//};


std::ostream& operator<<(std::ostream &out, const Point &p)
{
  out << "(" << p.x() << ", " << p.y() << ")";
  return out;
}

std::ostream& operator<<(std::ostream &out, const Line &l)
{
  out << "(" << l.A() << ", " << l.B() << ", " << l.C() << ")";
  return out;
}

}
