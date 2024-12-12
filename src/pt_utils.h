#pragma once
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

#define PI 3.14159265358979323846

inline float degrees_to_radians(float degrees) {
  return degrees * PI / 180.0;
}

inline float random_float() {
  return std::rand() / (RAND_MAX + 1.0);
}

inline float random_float(float min, float max) {
  return min + (max-min)*random_float();
}

inline vec3 random_unit_vector() {
  float rand_x = random_float(-1,1);
  float rand_y = random_float(-1,1);
  float rand_z = random_float(-1,1);
  return normalize(vec3(rand_x, rand_y, rand_z));
}

inline vec3 random_on_hemisphere(const vec3& normal) {
  vec3 on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, normal) > 0.0)
    return on_unit_sphere;
  else
    return -on_unit_sphere;
}