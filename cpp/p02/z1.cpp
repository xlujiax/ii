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

template<typename Iter>
  Iter next(Iter i)
{
  Iter tmp = i;
  ++tmp;
  return tmp;
}

template<typename Iter>
  void quick_sort(Iter begin, Iter end)
{
  std::cout << "[ ";
  std::copy(begin, end, std::ostream_iterator<int>(std::cout, " "));
  std::cout << "]" << std::endl;
    
  if(begin == end)
    return;
  
  if(next(begin) == end)
    if(*begin > *end)
    {
      std::swap(*begin, *end);
      return;
    }
  
  const Iter orig_begin = begin;
  const Iter orig_end = end;
  
  Iter pivot = begin;
  begin++;
  end--;

  // [ pivot, begin, ..., end ]

  while(begin != end && next(end) != begin)
  {
    while(*begin < *pivot) ++begin;
    while(*end > *pivot) --end;

    if(begin != end && next(end) != begin)
    {
      std::swap(*begin, *end);
      ++begin;
      --end;
    }
  }

  std::swap(*pivot, *begin);
  
  std::cout << "[ ";
  std::copy(orig_begin, orig_end, std::ostream_iterator<int>(std::cout, " "));
  std::cout << "]" << std::endl;

  quick_sort(orig_begin, begin);
  quick_sort(begin, orig_end);
}

template<typename Iter>
  void quick_sort2(Iter begin, Iter end)
{
  // W trakcie wykonywania algorytmu tracimy informację o oryginalnym przedziale,
  // dlatego zapamiętujemy go w poniższych stałych:
  const Iter first = begin;
  const Iter last = end;

  // przetwarzamy od elementu następnego po wybranym elemencie środkowym (first)
  ++begin;
  // przetwarzamy do końcowego elementu; end wskazuje na miejsce za ostatnim elementem, więc przesuwamy go na ostatni element
  --end;

  if(first != end && begin != end)
  {
    std::cout << "* middle is " << *first << std::endl;
    std::copy(first, last, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    while(begin != end && next(begin) != end)
    {
      std::cout << "[" << *begin << " " << *end << "]" << std::endl;
      
      while(*begin < *first && begin != end && next(begin) != end)
      {
	std::cout << "skip++ " << *begin << std::endl;
	
	++begin;
      }
      while(*end > *first && begin != end && next(begin) != end)
      {
	std::cout << "skip-- " << *end << std::endl;
	
	--end;
      }

      if(begin != end && next(begin) != end)
      {
	std::cout << "swap " << *begin << ", "<< *end << std::endl;
  
	std::swap(*begin, *end);
	++begin;
	--end;
      }
    }

    if(next(begin) == end)
    {
      if(*begin < *first)
	++begin;
      else
	++end;
    }
    
    // { begin == end <- wskazują na środkowy element}
    if(*begin <= *first)
      std::swap(*begin, *first);
    else
    {
      Iter t = begin;
      t--;
      std::swap(*t, *first);
    }

    std::cout << "po podziale " << std::endl;
    std::copy(first, last, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    quick_sort(first, begin);
    quick_sort(begin, last);
  }
  else
  {
    if(*first > *end)
    {
      std::swap(*first, *end);
    }
  }
}

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

template<typename T, typename Iter>
  bool test_aux(int N, Iter a_begin, Iter a_inserter, Iter b_begin, Iter b_inserter)
{
  /*std::generate_n(a_inserter, N, random_value<T>);
  std::copy(a_begin, a_inserter, b_inserter);

  std::sort(a_begin, a_inserter);
  bubble_sort(b_begin, b_inserter);

  return equal(a_begin, a_inserter, b_begin);*/
  return false;
}

template<typename T, typename Container>
  bool test(int, Container);

template<
  typename T,
  template<
    typename U,
    typename Alloc = std::allocator<U> >
  class Container>
  bool test(int N, Container<T> a)
{
  Container<T> b;
  return test_aux<T, typename Container<T>::iterator>(N, a.begin(), std::back_inserter(a), b.begin(), std::back_inserter(b));
}

template<>
  bool test<char, std::string>(int N, std::string a)
{
  std::string b;
  return test_aux<char, std::string::iterator>(N, a.begin(), std::back_inserter(a), b.begin(), std::back_inserter(b));
}
/*
template<typename T>
  bool test<T, T*>(int N, T* a)
{
  return false;
  }*/

int main(int, char*[])
{
  srand(time(0));
  
  if(test<std::string, std::vector>(10, std::vector<std::string>()))
    std::cout << "OK" << std::endl;
  else
    std::cout << "Niepowodzenie" << std::endl;
  
  return 0;
}
