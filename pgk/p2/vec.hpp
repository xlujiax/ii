#pragma once

#include <cmath>
#include <array>

constexpr float rad_to_deg(const float rad)
{
  return rad * 57.2957795;
}

struct vec3
{
  float x, y, z;
  float length() const { return sqrtf(x*x + y*y + z*z); }
  bool normal() const { return fabs(length() - 1.0f) < 0.01; }
  void normalize()
  {
    const float inv_len = 1.0f / length();
    x *= inv_len;
    y *= inv_len;
    z *= inv_len;
  }

  static vec3 cross(const vec3& a, const vec3& b)
  {
    return { a.y*b.z - a.z*b.y,
	a.z*b.x - a.x*b.z,
	a.x*b.y - a.y*b.x };
  }

  static float dot(const vec3& a, const vec3& b)
  {
    return a.x*b.x + a.y*b.y + a.z*b.z;
  }

  static float angle(const vec3& a, const vec3& b)
  {
    return acos(vec3::dot(a, b) / (a.length() * b.length()));
  }
};

struct vec2
{
  float x, y;
  float length() const { return sqrtf(x*x + y*y); }
};

struct quat
{
  float x, y, z, w;
  std::array<float, 16> get_rotation_matrix() const
  {
    return {{
	1.0f - 2.0f*y*y - 2.0f*z*z, 2.0f*x*y - 2.0f*z*w, 2.0f*x*z + 2.0f*y*w, 0.0f,
	  2.0f*x*y + 2.0f*z*w, 1.0f - 2.0f*x*x - 2.0f*z*z, 2.0f*y*z - 2.0f*x*w, 0.0f,
	  2.0f*x*z - 2.0f*y*w, 2.0f*y*z + 2.0f*x*w, 1.0f - 2.0f*x*x - 2.0f*y*y, 0.0f,
	  0.0f, 0.0f, 0.0f, 1.0f
	  }};
  }

  float length() const { return sqrtf(x*x + y*y + z*z + w*w); }
  void normalize()
  {
    const float inv_len = 1.0f / length();
    x *= inv_len;
    y *= inv_len;
    z *= inv_len;
    w *= inv_len;
  }
};

std::array<float, 16> multiply_matrices(const std::array<float, 16>& a, const std::array<float, 16>& b);

std::array<float, 16> identity_matrix();
