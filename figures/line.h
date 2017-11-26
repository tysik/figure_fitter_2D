#pragma once

#include <stdexcept>
#include <limits>

#include "figure.h"

namespace figfit
{

class Line : public Figure
{
public:
  Line(double A = 1.0, double B = 0.0, double C = 0.0) :
    normal_(A, B), offset_(C)
  {
    normalize();
  }

  Line(const Point &p1, const Point &p2) {
    double dx = p2.x() - p1.x();
    double dy = p2.y() - p1.y();

    if (dx == 0.0 && dy == 0.0)
      throw std::logic_error("Cannot calculate line parameters from two "
                             "identical points");

    if (dx != 0.0) {
      normal_ = Vec(dy / dx, -1.0);
      offset_ = p1.y() - normal_.x * p1.x();
    }
    else {
      normal_ = Vec(1.0, 0.0);
      offset_ = -p1.x();
    }

    normalize();
  }

  Line(const Line &l) :
    normal_(l.normal_), offset_(l.offset_)
  {}

  virtual Vec normal(const Point &p) const {
    // TODO: find direction to point
    return normal_;
  }

  double offset() const {
    return offset_;
  }

  bool isParallelTo(const Line &l) const {
    // TODO check anti parallels
    return (normal_ == l.normal_);
  }

  bool isPerpendicularTo(const Line &l) const {
    // TODO
    return true; // (A_ * l.A_ + B_ * l.B_ == 0.0);
  }

  virtual double distanceSquaredTo(const Point &point) const {
    return normal_.x * point.x ;
  }

  virtual double circumference() const {
    return std::numeric_limits<double>::infinity();
  }

  virtual double area() const {
    return 0.0;
  }

  friend std::ostream& operator<<(std::ostream &out, const Line &l) {
    out << "(" << l.A() << ", " << l.B() << ", " << l.C() << ")";
    return out;
  }

private:
  void normalize() {
    double length = normal_.length();
    if (length == 0.0)
      throw std::logic_error("Could not normalize line segment: A^2 + B^2 == 0");

    normal_ /= length;
    offset_ /= length;
  }

  Vec normal_;    // A, B
  double offset_; // C
};





///*
// * The function projects point onto the line supporting
// * the segment and checks if its projection falls on the
// * segment or not. In the first case the distance between
// * point and segment is computed. In the latter case the
// * distance between point and one of the edge points is
// * computed. Projected point is obtained from equation:
// * p = p1 + t * (p2 - p1)
// */
//virtual float getSmallestDistance(const Vec& point) const {
//  Vec p = point - origin();

//  Vec a = p2_ - p1_;
//  Vec b = p - p1_;
//  Vec c = p - p2_;

//  float t = a.dot(b) / a.lengthSquared();

//  if (t < 0.0)
//    return b.length();
//  else if (t > 1.0)
//    return c.length();

//  Vec projection = p1_ + t * a;
//  return (p - projection).length();
//}

//virtual float getArea() const {
//  return 0.0f;
//}

//float getLength() const {
//  return (p1_ - p2_).length();
//}






//class Segment : public Shape
//{
//public:
//  Segment(const Vec& p1 = Vec(), const Vec& p2 = Vec(1.0f, 0.0f), Vec* origin = nullptr)
//    : Shape(origin), p1_(p1), p2_(p2) {
//    assert(p1_ != p2_);
//  }

//  Segment(const Segment& segment)
//    : Shape(), p1_(segment.first_point()), p2_(segment.last_point()) {
//    origin_ = new Vec(segment.origin());
//  }


//  // Getters
//  Vec first_point() const { return p1_ + origin(); }
//  Vec last_point() const { return p2_ + origin(); }

//private:
//  Vec p1_;
//  Vec p2_;
//};

//#endif // SEGMENT_H
