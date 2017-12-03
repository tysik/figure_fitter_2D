#pragma once

#include <cmath>
#include <ostream>
#include <stdexcept>

namespace figfit
{

/**
 * @struct Vec vec.h
 *
 * @brief The Vec struct
 *
 * Structure containing 2D vector with x and y coordinates. It provides
 * overloads for most of arithmetic operators as well as pack of friend
 * functions for various operations on two vectors.
 */
struct Vec
{
  double x;   /**< @brief abscissa coordinate */
  double y;   /**< @brief ordinate coordinate */

  /**
   * @brief Construction from coordinates
   *
   * Note that default vector with x = 0, y = 0 is correct but methods like
   * normalized() are ill-defined.
   *
   * @param x is x coordinate
   * @param y is y coordinate
   */
  Vec(double x = 0.0, double y = 0.0) :
    x(x), y(y)
  {}

  /**
   * @brief Construction from copy
   * @param v is a rhs vector
   */
  Vec(const Vec &v) :
    x(v.x), y(v.y)
  {}

  /**
   * @brief Squared length of vector
   * @return squared length of the vector
   * @sa length()
   */
  double lengthSquared() const {
    return x * x + y * y;
  }

  /**
   * @brief Length of vector
   * @return length of the vector
   * @sa lengthSquared()
   */
  double length() const {
    return sqrt(lengthSquared());
  }

  /**
   * @brief Angle of vector
   *
   * The angle (orientation) of the vector is calculated in its coordinate
   * frame, where x is abscissa and y is ordinate.
   *
   * @return orientation of the vector in radians, in range [-pi, pi]
   * @sa angleDeg()
   */
  double angle() const {
    return atan2(y, x);
  }

  /**
   * @brief Angle of vector in degrees
   * @return orientation of the vector in degrees, in range [-180, 180]
   * @sa angle()
   */
  double angleDeg() const {
    return 180.0 * angle() / M_PI;
  }

  /**
   * @brief Dot product
   * @param v is another vector with which the dot product shall be computed
   * @return dot product of this vector and vector v
   */
  double dot(const Vec &v) const {
    return x * v.x + y * v.y;
  }

  /**
   * @brief Cross product z-coefficient
   *
   * In general, the cross product of two vectors generates a pseudovector.
   * For 2D case, since the z coordinate of each vector is assumed to be zero,
   * only the resulting z coordinate is computed.
   *
   * @param v is another vector with which the cross product shall be computed
   * @return z coordinate of cross product of this vector and vector v
   */
  double cross(const Vec &v) const {
    return x * v.y - y * v.x;
  }

  /**
   * @brief Normalized version of this vector
   * @return vector with the same orientation as this vector but with unit
   * length
   */
  Vec normalized() const {
    return *this / length();
  }

  /**
   * @brief Friend version of dot() method
   *
   * Note that dot(v1, v2) == dot(v2, v1).
   *
   * @param v1 is first vector
   * @param v2 is second vector
   * @return dot product of two vectors
   * @sa dot()
   */
  friend double dot(const Vec &v1, const Vec &v2) {
    return v1.dot(v2);
  }

  /**
   * @brief Friend version of cross() method
   *
   * Note that cross(v1, v2) != cross(v2, v1).
   *
   * @param v1 is first vector
   * @param v2 is second vector
   *
   * @return z coordinate of cross product of two vectors
   * @sa cross()
   */
  friend double cross(const Vec &v1, const Vec &v2) {
    return v1.cross(v2);
  }

  /**
   * @brief Friend version of the normalized() method
   *
   * Notice the names difference.
   *
   * @param v is a vector
   *
   * @return normalized version of provided vector
   * @sa normalized()
   */
  friend Vec normalize(const Vec &v) {
    return v / v.length();
  }

  /**
   * @brief Reflects vector against given normal vector
   *
   * Returns a vector as if it was reflected from the surface which normal
   * vector is given by parameter. Parameter normal is assumed to be normalized,
   * hence such check is not performed.
   *
   * @param normal is a normal vector
   *
   * @return reflected vector
   */
  Vec reflect(const Vec &normal) const {
    return *this - 2.0 * normal * (normal.dot(*this));
  }

  /**
   * @brief Perpendicular vector getter
   *
   * Returns a vector as if it was rotated 90 deg. in counter-clokwise
   * direction.
   *
   * @return vector perpendicular to this
   */
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
