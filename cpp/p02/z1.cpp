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

template<typename Iter>
  void quick_sort(Iter begin, Iter end)
{
  bubble_sort(begin, end);
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
    T* source = new T[N];
    T* bubble = new T[N];
    T* quick = new T[N];
    
    std::generate_n(source, N, random_value<T>);
    std::copy(source, source + N, bubble);
    std::copy(source, source + N, quick);

    std::sort(source, source + N);
    bubble_sort(bubble, bubble + N);
    quick_sort(quick, quick + N);

    return std::equal(source, source + N, bubble)
      && std::equal(source, source + N, quick);
  }
};

/*
  Dlaczego nie można przekazywać do testu niepełnych typów,
  np.
  --------------------------------------------
  Test<int, std::vector>()(5)
  --------------------------------------------

  zamiast
  
  --------------------------------------------
  Test<int, std::vector<int> >()(5)
  --------------------------------------------

  Przykład. Szablon pierwotny #1:
  
  --------------------------------------------
  template<typename U,
  template<
  typename U,
  typename A = std::allocator<U>
  > class T>
  struct F;
  --------------------------------------------

  Szablon pierwotny #2:
  
  --------------------------------------------
  template<typename U, typename T>
  struct F;
  --------------------------------------------

  Ukonkretnenienie działające tylko z szablonem pierwotnym #1.
  W przypadku szablonu bazowego #2 otrzymujemy błąd: redefinicja parametru szblonu - spodziewano się typu, otrzymano typ częściowo wyspecjalizowany

  --------------------------------------------
  template<typename U>
  struct F<U, std::list>
  {
  void f() { std::list<U> l; }
  };
  --------------------------------------------

  Ukonkretnienie działające tylko z szablonem pierwotnym #2.
  W przypadku szalonu bazowego #1 typ U* nie jest prawidłowym ukonkretnieniem typu template<typename, typename>class T.

  --------------------------------------------
  template<typename U>
  struct F<U, U*>
  {
  void f() { U* arr; }
  }
  --------------------------------------------
*/

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
    Cont<T> source;
    Cont<T> bubble;
    Cont<T> quick;
    
    std::generate_n(std::back_inserter(source), N, random_value<T>);
    std::copy(source.begin(), source.end(), std::back_inserter(bubble));
    std::copy(source.begin(), source.end(), std::back_inserter(quick));

    std::sort(source.begin(), source.end());
    bubble_sort(bubble.begin(), bubble.end());
    quick_sort(quick.begin(), quick.end());
    
    return std::equal(source.begin(), source.end(), bubble.begin())
      && std::equal(source.begin(), source.end(), quick.begin());
  }
};

template<typename T>
  struct Test<T, std::list<T> >
{
  bool operator()(const int N) const
  {
    std::list<T> source;
    std::list<T> bubble;
    std::list<T> quick;

    std::generate_n(std::back_inserter(source), N, random_value<T>);
    std::copy(source.begin(), source.end(), std::back_inserter(bubble));
    std::copy(source.begin(), source.end(), std::back_inserter(quick));

    source.sort();
    bubble_sort(bubble.begin(), bubble.end());
    quick_sort(quick.begin(), quick.end());
    
    return std::equal(source.begin(), source.end(), bubble.begin())
      && std::equal(source.begin(), source.end(), quick.begin());
  }
};

template<>
  struct Test<char, std::string >
{
  bool operator()(const int N) const
  {
    std::string source;
    std::string bubble;
    std::string quick;

    source = random_value<std::string>();
    std::copy(source.begin(), source.end(), std::back_inserter(bubble));
    std::copy(source.begin(), source.end(), std::back_inserter(quick));

    std::sort(source.begin(), source.end());
    bubble_sort(bubble.begin(), bubble.end());
    quick_sort(quick.begin(), quick.end());
    
    return std::equal(source.begin(), source.end(), bubble.begin())
      && std::equal(source.begin(), source.end(), quick.begin());
  }
};

int main(int, char*[])
{
  srand(time(0));

  static const int Size = 7;

  assert(( Test<int, int* >()(Size)                               ));
  assert(( Test<double, double* >()(Size)                         ));
  assert(( Test<std::string, std::string* >()(Size)               ));

  assert(( Test<int, std::list<int> >()(Size)                     ));
  assert(( Test<double, std::list<double> >()(Size)               ));
  assert(( Test<std::string, std::list<std::string> >()(Size)     ));
  
  assert(( Test<int, std::vector<int> >()(Size)                   ));
  assert(( Test<double, std::vector<double> >()(Size)             ));
  assert(( Test<std::string, std::vector<std::string> >()(Size)   ));
    
  assert(( Test<int, std::deque<int> >()(Size)                    ));
  assert(( Test<double, std::deque<double> >()(Size)              ));
  assert(( Test<std::string, std::deque<std::string> >()(Size)    ));
      
  assert(( Test<char, std::string>()(Size)                        ));

  std::cout << "Wszystkie testy zakończono powodzeniem" << std::endl;

  return 0;
}
