#pragma once

#include <math.h>

class vec
{
public:
  float x, y;
  vec(float X = 0, float Y = 0) : x(X), y(Y) {}
  vec operator +(const vec& c) const
  { return vec(x + c.x, y + c.y); }
  vec operator -(const vec& c) const
  { return vec(x - c.x, y - c.y); }
  vec operator *(const float f) const
  { return vec(x * f, y * f); }
  float length() const
  { return sqrt(x*x + y*y); }
  vec normal() const
  {
    const float inv = 1.0 / length();
    return vec(x * inv, y * inv);
  }
  
  friend float dot(const vec& a, const vec& b)
  { return a.x * b.x + a.y * b.y; }
  friend float cos_angle(const vec& a, const vec& b)
  { return dot(a,b) / (a.length() * b.length()); }
};
