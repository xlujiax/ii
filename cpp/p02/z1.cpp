// Maciej Pacut

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

// ---------------------
// procedury sortujące
// ---------------------

template<typename Iter>
  void bubble_sort(const Iter begin, const Iter end)
{
  Iter t = begin;

  while(t++ != end)
  {
    Iter a = begin;
    Iter b = begin;
    b++;

    // { a == b + 1 }

    while(b != end)
    {
      if(*a > *b)
      {
	typename std::iterator_traits<Iter>::value_type tmp(*a);
	*a = *b;
	*b = tmp;
      }
      
      ++a;
      ++b;
    }
  }
}

template<typename Iter>
  void quick_sort(const Iter begin, const Iter end)
{
  Iter lo = begin;
  Iter hi = end;

  const Iter pivot = begin;

  // przesuwamy lo, aby przetwarzać podsekwencję bez pivot
  // oraz przesuwamy hi, aby hi wskazywało na element sekwencji,
  // zamiast (wg konwencji STL) na miejsce za ostatnim elementem sekwencji
  ++lo, --hi;

  // jeśli sekwencja ma 0 lub 1 element;
  if(begin == end || lo == end)
    return;

  do
  {
    while(hi != lo && *lo <= *pivot) ++lo;
    while(hi != lo && *hi > *pivot) --hi;

    if(hi != lo)
    {
      typename std::iterator_traits<Iter>::value_type tmp(*lo);
      *lo = *hi;
      *hi = tmp;
    }
  }
  while(hi != lo);

  if(*hi > *pivot)
    --hi;
  
  typename std::iterator_traits<Iter>::value_type tmp(*pivot);
  *pivot = *hi;
  *hi = tmp;

  // sortowanie podsekwencji: (begin, pivot) i (pivot+1, end)
    
  quick_sort(begin, hi);
  ++hi;
  quick_sort(hi, end);
}

// ---------------------
// generatory losowych wartości
// ---------------------

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

// ---------------------
// testy
// ---------------------

template<typename Cont>
  struct Test;

template<typename T>
  struct Test<T*>
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

template<
  typename T,
  template<
    typename U,
    typename Alloc = std::allocator<U>
    > class Cont>
  struct Test<Cont<T> >
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
  struct Test<std::list<T> >
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
  struct Test<std::string >
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

// ---------------------
// punkt startowy programu
// ---------------------

int main(int, char*[])
{
  srand(time(0));

  for(int size = 0; size < 100; ++size)
  {
    assert(( Test<int* >()(size)                       ));
    assert(( Test<double* >()(size)                    ));
    assert(( Test<std::string* >()(size)               ));
    
    assert(( Test<std::list<int> >()(size)             ));
    assert(( Test<std::list<double> >()(size)          ));
    assert(( Test<std::list<std::string> >()(size)     ));
    
    assert(( Test<std::vector<int> >()(size)           ));
    assert(( Test<std::vector<double> >()(size)        ));
    assert(( Test<std::vector<std::string> >()(size)   ));
    
    assert(( Test<std::deque<int> >()(size)            ));
    assert(( Test<std::deque<double> >()(size)         ));
    assert(( Test<std::deque<std::string> >()(size)    ));
    
    assert(( Test<std::string>()(size)                 ));
  }
      
  std::cout << "Wszystkie testy zakończono powodzeniem" << std::endl;
  
  return 0;
}
