#pragma once

#include <cmath>
#include <ostream>
#include <stdexcept>

namespace figfit
{

struct Vec
{
  Vec(double x = 0.0, double y = 0.0) :
    x(x), y(y)
  {}

  Vec(const Vec &v) :
    x(v.x), y(v.y)
  {}

  double lengthSquared() const {
    return pow(x, 2.0) + pow(y, 2.0);
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

  void normalize() {
    double L = length();

    if (L == 0.0)
      throw std::logic_error("Cannot normalize vector of length 0");

    x /= L, y /= L;
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

  Vec operator-() {
    return Vec(-x, -y);
  }

  Vec operator+() {
    return Vec( x,  y);
  }

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

  friend double dot(const Vec &v1, const Vec &v2) {
    return v1.x * v2.x + v1.y * v2.y;
  }

  friend Vec cross(const Vec &v1, const Vec &v2) {
    return v1.x * v2.y - v1.y * v2.x;
  }

  friend Vec operator+(const Vec &v1, const Vec &v2) {
    return Vec(v1.x + v2.x, v1.y + v2.y);
  }

  friend Vec operator-(const Vec &v1, const Vec &v2) {
    return Vec(v1.x - v2.x, v1.y - v2.y);
  }

  friend Vec operator*(const double d, const Vec &v) {
    return Vec(d * v.x, d * v.y);
  }

  friend Vec operator*(const Vec &v, const double d) {
    return d * v;
  }

  friend Vec operator/(const Vec &v, const double d)  {
    return Vec(v.x / d, v.y / d);
  }

  friend bool operator==(const Vec &v1, const Vec &v2) {
    return (v1.x == v2.x && v1.y == v2.y);
  }

  friend bool operator!=(const Vec &v1, const Vec &v2) {
    return !(v1 == v2);
  }

  friend bool operator<(const Vec &v1, const Vec &v2) {
    return (v1.lengthSquared() < v2.lengthSquared());
  }

  friend bool operator<= (const Vec &v1, const Vec &v2) {
    return (v1.lengthSquared() <= v2.lengthSquared());
  }

  friend bool operator>(const Vec &v1, const Vec &v2) {
    return !(v1 <= v2);
  }

  friend bool operator>=(const Vec &v1, const Vec &v2) {
    return !(v1 < v2);
  }

  friend bool operator!(const Vec &v) {
    return (v.x == 0.0 && v.y == 0.0);
  }

  friend std::ostream& operator<<(std::ostream &out, const Vec &v) {
    out << "(" << v.x << ", " << v.y << ")"; return out;
  }

  double x;
  double y;
};

} // end namespace figfit
