#pragma once

#include "vector.hpp"

template<typename T, int Sz, int Get,
	 typename Rep1, typename Rep2>
  struct dp
{
  inline static const T value(const vector<T, Sz, Rep1>& a, const vector<T, Sz, Rep1>& b)
  {
    return a[Get] * b[Get] + dp<T, Sz, Get + 1, Rep1, Rep2>::value(a, b);
  }
};

template<typename T, int Sz,
	 typename Rep1, typename Rep2>
  struct dp<T, Sz, Sz, Rep1, Rep2>
{
  inline static const T value(const vector<T, Sz, Rep1>&, const vector<T, Sz, Rep1>&)
  {
    return 0;
  }
};

template<typename T, typename Rep1, typename Rep2, int Sz>
  T dot_product(const vector<T, Sz, Rep1>& a, const vector<T, Sz, Rep2>& b)
{
  return dp<T, Sz, 0, Rep1, Rep2>::value(a, b);
}
