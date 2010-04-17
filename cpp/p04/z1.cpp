#include <iostream>

struct empty {};
struct found {};
struct not_found {};

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

template<typename El, typename lst>
  struct find
{
  static const bool result = find<El, typename lst::tail>::result;
};

template<typename El, typename... lst>
  struct find<El, list<El, lst...> >
{
  static const bool result = true;
};

template<typename El1>
  struct find<El1, empty>
{
  static const bool result = false;
};

int main(int, char*[])
{
  std::cout << find<int, list<double, float, long, int> >::result << std::endl;
  
  return 0;
}
  
