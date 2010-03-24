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
  float random_value<float>() { return static_cast<float>(rand()) / static_cast<float>(RAND_MAX); }

template <>
  std::string random_value<std::string>()
{
  static const int MAX_LENGTH = 10;
  
  std::string s;
  std::generate_n(back_inserter(s), rand() % MAX_LENGTH, random_value<char>);
  return s;
}

template <>
  std::complex<float> random_value<std::complex<float> >()
{
  return std::complex<float>(random_value<float>(), random_value<float>());
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
    > class Cont >
  struct Test<T, Cont<T> >
{
  bool operator()(const int N) const
  {
    Cont<T> a;
    Cont<T> b;
    
    std::generate_n(std::back_inserter(a), N, random_value<T>);

    b = a;

    // ! back_inserter nie działa
    // std::copy(a.begin, a.end(), std::back_inserter(b));

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

    b = a;

    // ! back_inserter nie działa
    //std::copy(a.begin, a.end(), std::back_inserter(b));

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

    b = a;

    // ! back_inserter nie działa
    //std::copy(a.begin, a.end(), std::back_inserter(b));

    std::sort(a.begin(), a.end());
    bubble_sort(b.begin(), b.end());
    
    return std::equal(a.begin(), a.end(), b.begin());
  }
};

int main(int, char*[])
{
  srand(time(0));

  bool test = 
    Test<int, std::vector<int> >()(7) &&
    Test<int, int* >()(7)             &&
    Test<int, std::list<int> >()(7)   &&
    Test<int, std::deque<int> >()(7)   &&
    Test<char, std::string >()(7);

  if(test)
    std::cout << "OK" << std::endl;
  else
    std::cout << "Niepowodzenie" << std::endl;
  
  return 0;
}
