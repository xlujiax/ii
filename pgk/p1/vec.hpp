#pragma once

struct vec
{
  float x, y;

  vec(float X = 0, float Y = 0) : x(X), y(Y) {}
  vec operator +(const vec& c) const
  { return vec(x + c.x, y + c.y); }
  vec operator -(const vec& c) const
  { return vec(x - c.x, y - c.y); }
  vec operator *(const float f) const
  { return vec(x * f, y * f); }
};
