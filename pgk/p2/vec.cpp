#include "vec.hpp"

std::array<float, 16> multiply_matrices(const std::array<float, 16>& a, const std::array<float, 16>& b)
{
  std::array<float, 16> m;
  m[0] = a[0]*b[0]+a[1]*b[4]+a[2]*b[8]+a[3]*b[12];
  m[1] = a[0]*b[1]+a[1]*b[5]+a[2]*b[9]+a[3]*b[13];
  m[2] = a[0]*b[2]+a[1]*b[6]+a[2]*b[10]+a[3]*b[14];
  m[3] = a[0]*b[3]+a[1]*b[7]+a[2]*b[11]+a[3]*b[15];

  m[4] = a[4]*b[0]+a[5]*b[4]+a[6]*b[8]+a[7]*b[12];
  m[5] = a[4]*b[1]+a[5]*b[5]+a[6]*b[9]+a[7]*b[13];
  m[6] = a[4]*b[2]+a[5]*b[6]+a[6]*b[10]+a[7]*b[14];
  m[7] = a[4]*b[3]+a[5]*b[7]+a[6]*b[11]+a[7]*b[15];

  m[8] = a[8]*b[0]+a[9]*b[4]+a[10]*b[8]+a[11]*b[12];
  m[9] = a[8]*b[1]+a[9]*b[5]+a[10]*b[9]+a[11]*b[13];
  m[10] = a[8]*b[2]+a[9]*b[6]+a[10]*b[10]+a[11]*b[14];
  m[11] = a[8]*b[3]+a[9]*b[7]+a[10]*b[11]+a[11]*b[15];

  m[12] = a[12]*b[0]+a[13]*b[4]+a[14]*b[8]+a[15]*b[12];
  m[13] = a[12]*b[1]+a[13]*b[5]+a[14]*b[9]+a[15]*b[13];
  m[14] = a[12]*b[2]+a[13]*b[6]+a[14]*b[10]+a[15]*b[14];
  m[15] = a[12]*b[3]+a[13]*b[7]+a[14]*b[11]+a[15]*b[15];

  return m;
}

std::array<float, 16> identity_matrix()
{
  std::array<float, 16> m;
  m[0] = 1;  m[1] = 0;  m[2] = 0;  m[3] = 0;
  m[4] = 0;  m[5] = 1;  m[6] = 0;  m[7] = 0;
  m[8] = 0;  m[9] = 0;  m[10] = 1; m[11] = 0;
  m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
  return m;
}
