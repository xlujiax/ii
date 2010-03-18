#include <list>
#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <iterator>
#include <exception>
#include <algorithm>
#include <complex>

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
  // W trakcie wykonywania algorytmu tracimy informację o oryginalnym przedziale,
  // dlatego zapamiętujemy go w poniższych stałych:
  const Iter first = begin;
  const Iter last = end;

  ++begin;
  
  if(first != end && begin != end)
  {
    while(begin != end)
    {
      if(*begin < *first)
	++begin;
      else
      {
	--end;

	// end wskazuje na element za ostatnim elementem (wg konwencji STL),
	// dlatego zamieniamy *begin z elementem przed end
	Iter bef = end;
	--bef;
	
	std::swap(*begin, *bef);
      }
    }

    // { begin == end <- wskazują na środkowy element}
    std::swap(*begin, *first);
    
    quick_sort(first, begin);

    // zwiększamy begin, aby pominąć środkowy element,
    // który już jest na swoim miejscu
    quick_sort(++begin, last);
  }
}

template <typename T>
  T random_value();

template <>
  int random_value() { return rand() % 100; }

template <>
  float random_value() { return static_cast<float>(rand()) / static_cast<float>(RAND_MAX); }

template <>
  std::complex<float> random_value()
{
  return std::complex<float>(random_value<float>(), random_value<float>());
}

template<typename T, typename Cont>
  bool test(int);

template<
  typename T,
  template<
    typename U,
    typename Alloc = std::allocator<U> >
  class Container>
  bool test(int N)
{
  Container<T> cont;
  std::generate_n(std::back_inserter(cont), N, random_value<T>);

  Container<T> cont2;
  std::copy(cont.begin(), cont.end(), back_inserter(cont2));

  std::sort(cont2.begin(), cont2.end());

  return equal(cont.begin(), cont.end(), cont2.begin());
}

template<
  typename T,
  template<
    typename U,
    typename Alloc = std::allocator<U> >
  class Container >
  bool test(int N)
{
  std::list<T> cont;
  std::generate_n(std::back_inserter(cont), N, random_value<T>);

  std::list<T> cont2;
  std::copy(cont.begin(), cont.end(), back_inserter(cont2));

  cont2.sort();

  return equal(cont.begin(), cont.end(), cont2.begin());
}

int main(int, char*[])
{
  if(test<int, std::vector>(100))
    std::cout << "OK" << std::endl;
  else
    std::cout << "Niepowodzenie" << std::endl;
  
  if(test<int, std::list>(100))
    std::cout << "OK" << std::endl;
  else
    std::cout << "Niepowodzenie" << std::endl;
  return 0;
}
