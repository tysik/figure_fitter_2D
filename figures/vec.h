#pragma once

#include <cmath>
#include <ostream>
#include <stdexcept>

namespace figfit
{

struct Vec
{
  double x;
  double y;

  Vec(double x = 0.0, double y = 0.0) :
    x(x), y(y)
  {}

  Vec(const Vec &v) :
    x(v.x), y(v.y)
  {}

  //
  // Custom functions
  //
  double lengthSquared() const {
    return x * x + y * y;
  }

  double length() const {
    return sqrt(lengthSquared());
  }

  double angle() const {
    return atan2(y, x);
  }

  double angleDeg() const {
    return 180.0 * angle() / M_PI;
  }

  double dot(const Vec &v) const {
    return x * v.x + y * v.y;
  }

  double cross(const Vec &v) const {
    return x * v.y - y * v.x;
  }

  Vec normalized() const {
    return *this / length();
  }

  friend double dot(const Vec &v1, const Vec &v2) {
    return v1.dot(v2);
  }

  friend double cross(const Vec &v1, const Vec &v2) {
    return v1.cross(v2);
  }

  friend Vec normalize(const Vec &v) {
    return v / v.length();
  }


  /*
   * Returns a vector as if it was reflected from the surface
   * which normal vector is given by parameter. normal is assumed
   * to be normalized.
   */
  Vec reflect(const Vec &normal) const {
    return *this - 2.0 * normal * (normal.dot(*this));
  }

  Vec perpendicular() const {
    return Vec(-y, x);
  }

  //
  // Assignment operators
  //
  Vec& operator=(const Vec &v) {
    if (this != &v) {
      x = v.x; y = v.y;
    }
    return *this;
  }

  Vec& operator+=(const Vec &v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  Vec& operator-=(const Vec &v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  Vec& operator*=(double d) {
    x *= d;
    y *= d;
    return *this;
  }

  Vec& operator/=(double d) {
    x /= d;
    y /= d;
    return *this;
  }

  //
  // Arithmetic operators
  //
  Vec operator+() const {
    return Vec(x, y);
  }

  friend Vec operator+(const Vec &v1, const Vec &v2) {
    return Vec(v1.x + v2.x, v1.y + v2.y);
  }

  Vec operator-() const {
    return Vec(-x, -y);
  }

  friend Vec operator-(const Vec &v1, const Vec &v2) {
    return Vec(v1.x - v2.x, v1.y - v2.y);
  }

  friend Vec operator*(const double d, const Vec &v) {
    return Vec(d * v.x, d * v.y);
  }

  friend Vec operator*(const Vec &v, const double d) {
    return Vec(d * v.x, d * v.y);
  }

  friend Vec operator/(const Vec &v, const double d)  {
    return Vec(v.x / d, v.y / d);
  }

  //
  // Comparison operators
  //
  friend bool operator==(const Vec &v1, const Vec &v2) {
    return (v1.x == v2.x && v1.y == v2.y);
  }

  friend bool operator!=(const Vec &v1, const Vec &v2) {
    return !operator==(v1, v2);
  }

  friend bool operator<(const Vec &v1, const Vec &v2) {
    return (v1.lengthSquared() < v2.lengthSquared());
  }

  friend bool operator>(const Vec &v1, const Vec &v2) {
    return operator<(v2, v1);
  }

  friend bool operator<= (const Vec &v1, const Vec &v2) {
    return !operator>(v1, v2);
  }

  friend bool operator>=(const Vec &v1, const Vec &v2) {
    return !operator<(v1, v2);
  }

  //
  // Ostream operator
  //
  friend std::ostream& operator<<(std::ostream &out, const Vec &v) {
    out << "(" << v.x << ", " << v.y << ")"; return out;
  }
};

} // end namespace figfit
