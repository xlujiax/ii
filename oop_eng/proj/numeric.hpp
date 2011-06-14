#pragma once

#include <iostream>

template<typename T>
  class numeric
{
  T v;
  static int additions;
  static int multiplications;
  static int subtractions;
  static int divisions;
  static int instances_created;
  static int instances_current;
  static int instances_peak;
 public:
  numeric() { ++instances_created; ++instances_current; instances_peak = std::max(instances_current, instances_peak); }
 numeric(T t) : v(t) { ++instances_created; ++instances_current; instances_peak = std::max(instances_current, instances_peak); }
  ~numeric() { --instances_current; }
  numeric& operator=(const numeric<T>& n)
    {
      v = n.v;
      return *this;
    }
  friend numeric<T> operator+(const numeric<T>& a, const numeric<T>& b)
  {
    ++additions;
    
    numeric n;
    n.v = a.v + b.v;
    return n;
  }
  friend numeric<T> operator*(const numeric<T>& a, const numeric<T>& b)
  {
    ++multiplications;
    
    numeric n;
    n.v = a.v * b.v;
    return n;
  }
  friend numeric<T> operator/(const numeric<T>& a, const numeric<T>& b)
  {
    ++divisions;
    
    numeric n;
    n.v = a.v / b.v;
    return n;
  }
  friend numeric<T> operator-(const numeric<T>& a, const numeric<T>& b)
  {
    ++subtractions;
    
    numeric n;
    n.v = a.v - b.v;
    return n;
  }
  operator T() { return v; }
  T implicit_value() const { return v; }

  static void reset_report()
  {
    additions =
      multiplications =
      divisions =
      instances_created =
      instances_peak =
      instances_current =
      subtractions = 0;
  }

  static void usage_report()
  {
    std::cout << " *** " << std::endl
	      << "additions: " << additions << std::endl
	      << "multiplications: " << multiplications << std::endl
	      << "divisions: " << divisions << std::endl
	      << "subtractions: " << subtractions << std::endl
	      << "instances created: " << instances_created << std::endl
	      << "instances peak: " << instances_peak << std::endl
	      << " *** " << std::endl;
  }
};


template<typename T>
  int numeric<T>::additions = 0;
template<typename T>
  int numeric<T>::multiplications = 0;
template<typename T>
  int numeric<T>::subtractions = 0;
template<typename T>
  int numeric<T>::divisions = 0;
template<typename T>
  int numeric<T>::instances_created = 0;
template<typename T>
  int numeric<T>::instances_current = 0;
template<typename T>
  int numeric<T>::instances_peak = 0;
