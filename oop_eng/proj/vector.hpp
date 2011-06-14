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

