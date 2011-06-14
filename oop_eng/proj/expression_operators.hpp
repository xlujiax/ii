#pragma once

#include "vector.hpp"
#include "expression_tree.hpp"

template <typename T, int Sz, typename R1, typename R2>
  const vector<T, Sz, addition_operator<T, R1, R2> >
  operator+(const vector<T, Sz, R1>& a, const vector<T, Sz, R2>& b)
{
  return vector<T, Sz, addition_operator<T,R1,R2> >(addition_operator<T,R1,R2>(a.get_rep(), b.get_rep()));
}

template <typename T, int Sz, typename R1, typename R2>
  const vector<T, Sz, multiplication_operator<T, R1, R2> >
  operator*(const vector<T, Sz, R1>& a, const vector<T, Sz, R2>& b)
{
  return vector<T, Sz, multiplication_operator<T,R1,R2> >(multiplication_operator<T,R1,R2>(a.get_rep(), b.get_rep()));
}

template <typename T, int Sz, typename R1, typename R2>
  const vector<T, Sz, division_operator<T, R1, R2> >
  operator/(const vector<T, Sz, R1>& a, const vector<T, Sz, R2>& b)
{
  return vector<T, Sz, division_operator<T,R1,R2> >(division_operator<T,R1,R2>(a.get_rep(), b.get_rep()));
}

template <typename T, int Sz, typename R1, typename R2>
  const vector<T, Sz, subtraction_operator<T, R1, R2> >
  operator-(const vector<T, Sz, R1>& a, const vector<T, Sz, R2>& b)
{
  return vector<T, Sz, subtraction_operator<T,R1,R2> >(subtraction_operator<T,R1,R2>(a.get_rep(), b.get_rep()));
}
