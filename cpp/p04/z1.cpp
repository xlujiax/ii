#include <iostream>

struct empty {};

template<typename...> struct
  list;

template<>
  struct list<>
{
  typedef empty T;
};

template<typename H, typename... T>
  struct list<H, T...>
{
  typedef list<T...> tail;
};

template<typename El1, typename El2, typename lst>
  struct find_first
{
  typedef typename find_first<El1, El2, typename lst::tail>::result result;
};

template<typename El1, typename El2, typename... lst>
  struct find_first<El1, El2, list<El1, lst...> >
{
  typedef El1 result;
};

template<typename El1, typename El2, typename... lst>
  struct find_first<El1, El2, list<El2, lst...> >
{
  typedef El2 result;
};

template<typename El, typename... lst>
  struct find_first<El, El, list<El, lst...> >
{
  typedef El result;
};

template<typename El1, typename El2>
  struct find_first<El1, El2, list<> >
{
  typedef void result;
};

typedef list<double,
	     float,
	     unsigned long long,
	     long long,
	     unsigned long int,
	     long int,
	     unsigned int,
	     int,
	     unsigned short,
	     short,
	     unsigned char,
	     char,
	     bool> priority;


template<typename T>
  struct bare
{ typedef T type; };

template<typename T>
  struct bare<T&>
{ typedef T type; };

template<typename T, typename U>
  typename find_first<
  typename bare<T>::type,
  typename bare<U>::type, priority
  >::result
  max(T t, U u)
{
  return (t > u) ? t : u;
}

int main(int, char*[])
{
  const double ci = 9;
  int i = 1;
  int& ri = i;
  std::cout << max(ci, ri) << std::endl;
  return 0;
}
  