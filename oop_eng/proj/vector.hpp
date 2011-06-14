#pragma once

#include <string>

template<typename T, int Size>
  class vector_data
{
  T data[Size];
public:
  vector_data() {}
  vector_data(const vector_data<T, Size>& v)
  {
    for(int i = 0; i < size(); ++i)
      data[i] = v[i];
  }

  T& operator[](int i) { return data[i]; }
  T operator[](int i) const { return data[i]; }
  
  typedef T element_type;
  
  static int size() { return Size; }
  std::string name() const { return "vector data"; }
};

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

template<typename T, int Size, typename Rep = vector_data<T, Size> >
  class vector
{
  Rep rep;
public:
  vector() {}
  vector(Rep const& r) : rep(r) {}
  vector& operator=(const vector& b)
  {
    for(int i = 0; i < b.size(); ++i)
      rep[i] = b[i];
    return *this;
  }
  template<typename T2, typename Rep2>
    vector& operator= (const vector<T2, Size, Rep2>& b)
  {
    for(int i = 0; i < b.size(); ++i)
      rep[i] = b[i];
    return *this;
  }
  int size() const { return rep.size(); }
  T operator[](int i) const { return rep[i]; }
  T& operator[](int i) { return rep[i]; }
  const Rep& get_rep() const { return rep; }
};

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
