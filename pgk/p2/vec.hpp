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
  vec3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
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
  vec2(float X = 0, float Y = 0) : x(X), y(Y) {}
  float length() const { return sqrtf(x*x + y*y); }
};

struct quat
{
  float x, y, z, w;
  std::array<float, 16> get_rotation_matrix() const
  {
    /*
    return {{
	1.0f - 2.0f*y*y - 2.0f*z*z, 2.0f*x*y - 2.0f*z*w, 2.0f*x*z + 2.0f*y*w, 0.0f,
	  2.0f*x*y + 2.0f*z*w, 1.0f - 2.0f*x*x - 2.0f*z*z, 2.0f*y*z - 2.0f*x*w, 0.0f,
	  2.0f*x*z - 2.0f*y*w, 2.0f*y*z + 2.0f*x*w, 1.0f - 2.0f*x*x - 2.0f*y*y, 0.0f,
	  0.0f, 0.0f, 0.0f, 1.0f
	  }};
    */
    std::array<float, 16> m;
    m[0] = 1.0f - 2.0f*y*y - 2.0f*z*z;
    m[1] = 2.0f*x*y - 2.0f*z*w;
    m[2] = 2.0f*x*z + 2.0f*y*w;
    m[3] = 0.0f;
    m[4] = 2.0f*x*y + 2.0f*z*w;
    m[5] = 1.0f - 2.0f*x*x - 2.0f*z*z;
    m[6] = 2.0f*y*z - 2.0f*x*w;
    m[7] = 0.0f;
    m[8] = 2.0f*x*z - 2.0f*y*w;
    m[9] = 2.0f*y*z + 2.0f*x*w;
    m[10] = 1.0f - 2.0f*x*x - 2.0f*y*y;
    m[11] = 0.0f;
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
    return m;
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
