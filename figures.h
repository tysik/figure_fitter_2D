#pragma once

#include <cmath>

namespace figfit
{

double sqr(double x) { return pow(x, 2.0); }

class Figure
{};

class Point : public Figure
{
public:
  Point() : x(0.0), y(0.0) {}

  Point(double x, double y) : x(x), y(y) {}

  Point(const Point &p) : x(p.x), y(p.y) {}

  double x;
  double y;
};

class Line : public Figure
{
public:
  Line() : A(1.0), B(0.0), C(0.0) {}

  Line(double A, double B, double C) : A(A), B(B), C(C)
  {
    double D = sqrt(sqr(A) + sqr(B));
    this->A /= D; this->B /= D; this->C /= D;
  }

  Line(const Point &p1, const Point &p2)
  {
    // TODO
  }

  Line(const Line &l) : A(l.A), B(l.B), C(l.C) {}

  double A, B, C;
};

class Segment : public Line
{
public:
  Segment() {}

  Point first;
  Point last;
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


class Box : public Figure
{
public:
  Box() {}

  Segment N, E, S, W;
};

}
