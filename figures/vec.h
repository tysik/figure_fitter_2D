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
 * functions for various operations on two vectors. The representation uses
 * right-handed coordinate system, hence the angle is growing in the counter-
 * clokwise direction.
 */
struct Vec
{
  double x;   /**< @brief abscissa coordinate */
  double y;   /**< @brief ordinate coordinate */

  /**
   * @brief Construction from coordinates (default)
   *
   * Note that default vector with x = 0, y = 0 is correct but methods like
   * normalized() will throw exceptions due to the length = 0.
   *
   * @param x is an abscissa coordinate
   * @param y is an ordinate coordinate
   */
  Vec(double x = 0.0, double y = 0.0) :
    x(x), y(y)
  {}

  Vec(const Vec& rhs) = default;
  Vec(Vec&& rhs) = default;

  /**
   * @brief Get length of this vector
   *
   * @return length of this vector
   *
   * @sa lengthSquared()
   */
  double length() const {
    return sqrt(lengthSquared());
  }

  /**
   * @brief Get length of a given vector
   *
   * @param v is a given vector
   *
   * @return length of a given vector
   */
  friend double length(const Vec& v) {
    return v.length();
  }

  /**
   * @brief Get squared length of this vector
   *
   * Calculation of squared length is faster than calculation of length.
   *
   * @return squared length of this vector
   *
   * @sa length()
   */
  double lengthSquared() const {
    return x * x + y * y;
  }

  /**
   * @brief Get squared length of a given vector
   *
   * @param v is a given vector
   *
   * @return length of a given vector
   */
  friend double lengthSquared(const Vec& v) {
    return v.length();
  }

  /**
   * @brief Get angle of this vector
   *
   * @return orientation of this vector in radians, in range [-pi, pi]
   *
   * @sa angleDeg()
   */
  double angle() const {
    return atan2(y, x);
  }

  /**
   * @brief Get angle of a given vector
   *
   * @return orientation of a given vector in radians, in range [-pi, pi]
   */
  friend double angle(const Vec& v) {
    return v.angle();
  }

  /**
   * @brief Get angle of this vector in degrees
   *
   * @return orientation of this vector in degrees, in range [-180, 180]
   *
   * @sa angle()
   */
  double angleDeg() const {
    return 180.0 * angle() / M_PI;
  }

  /**
   * @brief Get angle of a given vector in degrees
   *
   * @return orientation of a given vector in degrees, in range [-180, 180]
   */
  friend double angleDeg(const Vec& v) {
    return v.angleDeg();
  }

  /**
   * @brief Get dot product of this vector with a given vector
   *
   * @param v is a given vector
   *
   * @return dot product of this vector and vector v
   *
   * @sa cross()
   */
  double dot(const Vec& v) const {
    return x * v.x + y * v.y;
  }

  /**
   * @brief Get dot product of two vectors
   *
   * Note that dot(v1, v2) = dot(v2, v1).
   *
   * @param v1 is a first vector
   * @param v2 is a second vector
   *
   * @return dot product of two vectors
   */
  friend double dot(const Vec& v1, const Vec& v2) {
    return v1.dot(v2);
  }

  /**
   * @brief Get z-coordinate of cross product of this vector with a given vector
   *
   * In general, the cross product of two vectors generates a pseudovector.
   * For 2D case, since the z coordinate of each vector is assumed to be zero,
   * only the resulting z coordinate is computed.
   *
   * @param v is a given vector
   *
   * @return z-coordinate of a cross product of this vector and vector v
   *
   * @sa dot()
   */
  double cross(const Vec& v) const {
    return x * v.y - y * v.x;
  }

  /**
   * @brief Get z-coordinate of cross product of two vectors
   *
   * Note that cross(v1, v2) = -cross(v2, v1).
   *
   * @param v1 is a first vector
   * @param v2 is a second vector
   *
   * @return z-coordinate of cross product of two vectors
   */
  friend double cross(const Vec& v1, const Vec& v2) {
    return v1.cross(v2);
  }

  /**
   * @brief Normalize this vector
   *
   * @return reference to this vector after normalization
   *
   * @throw std::logic_error if the length of the vector is zero
   */
  Vec& normalize() {
    double length = this->length();
    if (length == 0.0)
      throw std::logic_error("Cannot normalize a vector of length zero.");

    x /= length;
    y /= length;

    return *this;
  }

  /**
   * @brief Normalize a given vector
   *
   * @param v is a given vector
   *
   * @return reference to v after normalization
   *
   * @throw std::logic_error if the length of the vector is zero
   *
   * @sa normalize()
   */
  friend Vec& normalize(Vec& v) {
    return v.normalize();
  }

  /**
   * @brief Get normalized copy of this vector
   *
   * @return normalized copy of this vector
   *
   * @throw std::logic_error if the length of the vector is zero
   *
   * @sa normalize()
   */
  Vec normalized() const {
    Vec v = *this;
    return v.normalize();
  }

  /**
   * @brief Get normalized copy of a given vector
   *
   * @param v is a given vector
   *
   * @return normalized copy of a given vector
   *
   * @throw std::logic_error if the length of the vector is zero
   *
   * @sa normalize()
   */
  friend Vec normalized(const Vec& v) {
    return v.normalized();
  }

  /**
   * @brief Rotate this vector
   *
   * Rotation is applied in a counter-clokwise direction.
   *
   * @param angle is an angle of rotation in radians
   *
   * @return reference to this vector after rotation
   */
  Vec& rotate(double angle) {
    double x_tmp = x * cos(angle) - y * sin(angle);
    double y_tmp = x * sin(angle) + y * cos(angle);

    x = x_tmp;
    y = y_tmp;

    return *this;
  }

  /**
   * @brief Rotate a given vector
   *
   * Rotation is applied in a counter-clokwise direction.
   *
   * @param v is a given vector
   * @param angle is an angle of rotation in radians
   *
   * @return reference to v after rotation
   *
   * @sa rotate()
   */
  friend Vec& rotate(Vec& v, double angle) {
    return v.rotate(angle);
  }

  /**
   * @brief Get rotated copy of this vector
   *
   * @param angle is an angle of rotation in radians
   *
   * @return rotated copy of this vector
   *
   * @sa rotate()
   */
  Vec rotated(double angle) const {
    Vec v = *this;
    return v.rotate(angle);
  }

  /**
   * @brief Get rotated copy of a given vector
   *
   * @param v is a given vector
   * @param angle is an angle of rotation in radians
   *
   * @return rotated copy of v
   *
   * @sa rotate()
   */
  friend Vec rotated(const Vec& v, double angle) {
    return v.rotated(angle);
  }

  /**
   * @brief Rotate this vector by 90 degrees
   *
   * @return reference to this vector after rotation by 90 degrees in counter-
   * clokwise direction
   *
   * @sa rotate()
   */
  Vec& rotate90() {
    double x_tmp = -y;
    double y_tmp = x;

    x = x_tmp;
    y = y_tmp;

    return *this;
  }

  /**
   * @brief Rotate a given vector by 90 degrees
   *
   * @param v is a given vector
   *
   * @return reference to a given vector after rotation by 90 degrees in
   * counter-clokwise direction
   *
   * @sa rotate()
   */
  friend Vec& rotate90(Vec& v) {
    return v.rotate90();
  }

  /**
   * @brief Get a copy of this vector rotated by 90 deg
   *
   * @return a copy of this vector rotated by 90 deg
   *
   * @sa rotate90()
   */
  Vec rotated90() const {
    Vec v = *this;
    return v.rotate90();
  }

  /**
   * @brief Get a copy of a given vector rotated by 90 deg
   *
   * @param v is a given vector
   *
   * @return a copy of a given vector rotated by 90 deg
   *
   * @sa rotate()
   */
  friend Vec rotated90(const Vec& v) {
    return v.rotated90();
  }

  /**
   * @brief Reflect this vector against a given normal vector
   *
   * Returns a vector as if it "bounced" from the surface which normal was given
   * by the parameter. Parameter normal is assumed to be normalized, hence such
   * check is not performed.
   *
   * @param normal is a normal vector
   *
   * @return reference to this vector after reflection
   */
  Vec& reflect(const Vec& normal) {
    *this = *this - 2.0 * normal * normal.dot(*this);
    return *this;
  }

  /**
   * @brief Reflect a given vector against a given normal vector
   *
   * @param v is a given vector
   *
   * @param normal is a normal vector
   *
   * @return reference to a given vector after reflection
   *
   * @sa reflect()
   */
  friend Vec& reflect(Vec& v, const Vec& normal) {
    return v.reflect(normal);
  }

  /**
   * @brief Get a copy of this vector reflected against a given normal vector
   *
   * @param normal is a given normal vector
   *
   * @return copy of this vector reflected against a given normal vector
   *
   * @sa reflect()
   */
  Vec reflected(const Vec& normal) const {
    Vec v = *this;
    return v.reflect(normal);
  }

  /**
   * @brief Get a copy of a given vector reflected agains a given normal vector
   *
   * @param v is a given vector
   *
   * @param normal is a given normal vector
   *
   * @return a copy of a given vector reflected agains a given normal vector
   *
   * @sa reflect()
   */
  friend Vec reflected(const Vec& v, const Vec& normal) {
    return v.reflected(normal);
  }

  //
  // Assignment operators
  //
  Vec& operator=(const Vec& v) = default;
  Vec& operator=(Vec&& v) = default;

  Vec& operator+=(const Vec& v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  Vec& operator-=(const Vec& v) {
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

  friend Vec operator+(const Vec& v1, const Vec& v2) {
    return Vec(v1.x + v2.x, v1.y + v2.y);
  }

  Vec operator-() const {
    return Vec(-x, -y);
  }

  friend Vec operator-(const Vec& v1, const Vec& v2) {
    return Vec(v1.x - v2.x, v1.y - v2.y);
  }

  friend Vec operator*(const double d, const Vec& v) {
    return Vec(d * v.x, d * v.y);
  }

  friend Vec operator*(const Vec& v, const double d) {
    return Vec(d * v.x, d * v.y);
  }

  friend Vec operator/(const Vec& v, const double d)  {
    return Vec(v.x / d, v.y / d);
  }

  //
  // Comparison operators
  //
  friend bool operator==(const Vec& v1, const Vec& v2) {
    return (v1.x == v2.x && v1.y == v2.y);
  }

  friend bool operator!=(const Vec& v1, const Vec& v2) {
    return !operator==(v1, v2);
  }

  friend bool operator<(const Vec& v1, const Vec& v2) {
    return (v1.lengthSquared() < v2.lengthSquared());
  }

  friend bool operator>(const Vec& v1, const Vec& v2) {
    return operator<(v2, v1);
  }

  friend bool operator<= (const Vec& v1, const Vec& v2) {
    return !operator>(v1, v2);
  }

  friend bool operator>=(const Vec& v1, const Vec& v2) {
    return !operator<(v1, v2);
  }

  //
  // Ostream operator
  //
  friend std::ostream& operator<<(std::ostream& out, const Vec& v) {
    out << "(" << v.x << ", " << v.y << ")"; return out;
  }
};

} // end namespace figfit
