#pragma once
#include <iostream>
#include <cmath>

class vec3 {

public:
  float elements[3];

  vec3():
    elements{0, 0, 0}
  {}
  vec3(float e0, float e1, float e2):
    elements{e0, e1, e2}
  {}

  inline float x() const { return elements[0]; }
  inline float y() const { return elements[1]; }
  inline float z() const { return elements[2]; }

  vec3 operator-() const { return vec3(-elements[0], -elements[1], -elements[2]); }
  float operator[](int i) const { return elements[i]; }
  float& operator[](int i) { return elements[i]; }

  vec3& operator+=(const vec3& v) {
    elements[0] += v.elements[0];
    elements[1] += v.elements[1];
    elements[2] += v.elements[2];
    return *this;
  }

  vec3& operator*=(float t) {
    elements[0] *= t;
    elements[1] *= t;
    elements[2] *= t;
    return *this;
  }

  vec3& operator/=(float t) {
    return *this *= 1/t;
  }

  float length() const {
    return std::sqrt(length_squared());
  }

  float length_squared() const {
    return elements[0]*elements[0] + elements[1]*elements[1] + elements[2]*elements[2];
  }
};


inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.elements[0] + v.elements[0], u.elements[1] + v.elements[1], u.elements[2] + v.elements[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.elements[0] - v.elements[0], u.elements[1] - v.elements[1], u.elements[2] - v.elements[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.elements[0] * v.elements[0], u.elements[1] * v.elements[1], u.elements[2] * v.elements[2]);
}

inline vec3 operator*(float t, const vec3& v) {
    return vec3(t*v.elements[0], t*v.elements[1], t*v.elements[2]);
}

inline vec3 operator*(const vec3& v, float t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, float t) {
    return (1/t) * v;
}

inline float dot(const vec3& u, const vec3& v) {
    return u.elements[0] * v.elements[0]
         + u.elements[1] * v.elements[1]
         + u.elements[2] * v.elements[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.elements[1] * v.elements[2] - u.elements[2] * v.elements[1],
                u.elements[2] * v.elements[0] - u.elements[0] * v.elements[2],
                u.elements[0] * v.elements[1] - u.elements[1] * v.elements[0]);
}

inline vec3 normalize(const vec3& v) {
    return v / v.length();
}

