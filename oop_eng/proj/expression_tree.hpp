#pragma once

#include "vector.hpp"

template<typename T>
  struct expr
{
  typedef const T& type;
};

template<typename T, typename L, typename R>
  class addition_operator
{
  typename expr<L>::type l;
  typename expr<R>::type r;
public:
  addition_operator(const L& ll, const R& rr) : l(ll), r(rr)  {}
  T operator[](int i) const { return l[i] + r[i]; }
  int size() const { return (l.size() == 0) ? r.size() : l.size(); }
  std::string name() const { return "addition"; }
};

template<typename T, typename L, typename R>
  class multiplication_operator
{
  typename expr<L>::type l;
  typename expr<R>::type r;
public:
  multiplication_operator(const L& ll, const R& rr) : l(ll), r(rr)  {}
  T operator[](int i) const { return l[i] * r[i]; }
  int size() const { return (l.size() == 0) ? r.size() : l.size(); }
  std::string name() const { return "multiplication"; }
};

template<typename T, typename L, typename R>
  class division_operator
{
  typename expr<L>::type l;
  typename expr<R>::type r;
public:
  division_operator(const L& ll, const R& rr) : l(ll), r(rr)  {}
  T operator[](int i) const { return l[i] / r[i]; }
  int size() const { return (l.size() == 0) ? r.size() : l.size(); }
  std::string name() const { return "division"; }
};

template<typename T, typename L, typename R>
  class subtraction_operator
{
  typename expr<L>::type l;
  typename expr<R>::type r;
public:
  subtraction_operator(const L& ll, const R& rr) : l(ll), r(rr)  {}
  T operator[](int i) const { return l[i] - r[i]; }
  int size() const { return (l.size() == 0) ? r.size() : l.size(); }
  std::string name() const { return "subtraction"; }
};

template<typename T>
  class scalar
{
  T rep;
public:
  scalar(T const& s) : rep(s) {}
  T operator[] (int) const { return rep; }
  std::string name() const { return "scalar"; }
};
