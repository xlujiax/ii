#include <list>
#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <iterator>
#include <exception>
#include <algorithm>
#include <complex>
#include <ctime>
#include <cassert>

template<typename Iter>
  void bubble_sort(Iter begin, Iter end)
{
  Iter t = begin;

  while(t++ != end)
  {
    Iter a = begin;
    Iter b = begin;
    b++;
    
    while(b != end)
    {
      if(*a > *b)
      {
	std::swap(*a, *b);
      }
      
      ++a;
      ++b;
    }
  }
}

// generatory losowych wartości
// {

template <typename T>
  T random_value();

template <>
  int random_value<int>() { return rand() % 100; }

template <>
  char random_value<char>() { return rand() % 26 + 65; }

template <>
  double random_value<double>() { return static_cast<double>(rand()) / static_cast<double>(RAND_MAX); }

template <>
  std::string random_value<std::string>()
{
  static const int MAX_LENGTH = 10;
  
  std::string s;
  std::generate_n(back_inserter(s), rand() % MAX_LENGTH, random_value<char>);
  return s;
}

// }
// generatory losowych wartości

template<typename T, typename Cont>
  struct Test;

template<typename T>
  struct Test<T, T*>
{
  bool operator()(const int N) const
  {
    T* a = new T[N];
    T* b = new T[N];
    
    std::generate_n(a, N, random_value<T>);
    std::copy(a, a + N, b);

    std::sort(a, a + N);
    bubble_sort(b, b + N);

    return std::equal(a, a + N, b);
  }
};

template<
  typename T,
  template<
    typename U,
    typename Alloc = std::allocator<U>
    > class Cont>
  struct Test<T, Cont<T> >
{
  bool operator()(const int N) const
  {
    Cont<T> a;
    Cont<T> b;
    
    std::generate_n(std::back_inserter(a), N, random_value<T>);
    std::copy(a.begin(), a.end(), std::back_inserter(b));

    std::sort(a.begin(), a.end());
    bubble_sort(b.begin(), b.end());
    
    return std::equal(a.begin(), a.end(), b.begin());
  }
};

template<typename T>
  struct Test<T, std::list<T> >
{
  bool operator()(const int N) const
  {
    std::list<T> a;
    std::list<T> b;

    std::generate_n(std::back_inserter(a), N, random_value<T>);
    std::copy(a.begin(), a.end(), std::back_inserter(b));

    a.sort();
    bubble_sort(b.begin(), b.end());
    
    return std::equal(a.begin(), a.end(), b.begin());
  }
};

template<>
  struct Test<char, std::string >
{
  bool operator()(const int N) const
  {
    std::string a;
    std::string b;

    std::generate_n(std::back_inserter(a), N, random_value<char>);
    std::copy(a.begin(), a.end(), std::back_inserter(b));

    std::sort(a.begin(), a.end());
    bubble_sort(b.begin(), b.end());
    
    return std::equal(a.begin(), a.end(), b.begin());
  }
};

int main(int, char*[])
{
  srand(time(0));

  static const int Size = 7;

  assert(( Test<int, int* >()(Size)                 ));
  assert(( Test<double, double* >()(Size)           ));
  assert(( Test<std::string, std::string* >()(Size) ));

  assert(( Test<int, std::list<int> >()(Size)   ));
  assert(( Test<double, std::list<double> >()(Size)  ));
  assert(( Test<std::string, std::list<std::string> >()(Size)     ));
  
  assert(( Test<int, std::vector<int> >()(Size) ));
    assert(( Test<double, std::vector<double> >()(Size) ));
    assert(( Test<std::string, std::vector<std::string> >()(Size) ));
    
    assert(( Test<int, std::deque<int> >()(Size) ));
      assert(( Test<double, std::deque<double> >()(Size) ));
      assert(( Test<std::string, std::deque<std::string> >()(Size) ));
      
      assert(( Test<char, std::string>()(Size) ));

  std::cout << "Wszystkie testy zakończono powodzeniem" << std::endl;

  return 0;
}
