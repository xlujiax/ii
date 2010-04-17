#include <iostream>
#include <typeinfo>
#include <limits>
#include <cassert>

// http://www.cplusplus.com/doc/tutorial/variables/

/*
 * Lista szablonowa
 */

struct empty {};

template<typename...> struct
  list;

template<>
  struct list<>
{ typedef empty T; };

template<typename H, typename... T>
  struct list<H, T...>
{ typedef list<T...> tail; };

/*
 * Wyszukiwanie w liście pierwszego z dwóch elementów El1, El2
 * Zwraca pierwszy napotkany typ lub void w przypadku nie znalezienia żadnego typu
 */

template<typename El1, typename El2, typename lst>
  struct find_first
{ typedef typename find_first<El1, El2, typename lst::tail>::result result; };

template<typename El1, typename El2, typename... lst>
  struct find_first<El1, El2, list<El1, lst...> >
{ typedef El1 result; };

template<typename El1, typename El2, typename... lst>
  struct find_first<El1, El2, list<El2, lst...> >
{ typedef El2 result; };

template<typename El, typename... lst>
  struct find_first<El, El, list<El, lst...> >
{ typedef El result; };

template<typename El1, typename El2>
  struct find_first<El1, El2, list<> >
{ typedef void result; };

/*
 * Porządek na typach
 */

typedef list<long double,
	     double,
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
/*
 * Cecha wyciągająca typ
 * Mapowanie:
 * T -> T
 * T& -> T
 * T* -> T
 * const T* -> T
 * const T& -> T
 */

template<typename T>
  struct bare
{ typedef T type; };

template<typename T>
  struct bare<T&>
{ typedef T type; };

template<typename T>
  struct bare<T*>
{ typedef T type; };

template<typename T>
  struct bare<const T*>
{ typedef T type; };

template<typename T>
  struct bare<const T&>
{ typedef T type; };

/*
 * Właściwa wartość zmiennej - dereferencja, kiedy potrzebna
 */

template<typename T>
  inline typename bare<T>::type value(T t)
{ return t; }

template<typename T>
  inline typename bare<T>::type value(T* t)
{ return *t; }

/*
 * Szablon max
 */

template<typename T, typename U>
  typename find_first<
  typename bare<T>::type,
  typename bare<U>::type, priority
  >::result
  max(T t, U u)
{
  return (value(t) > value(u)) ? value(t) : value(u);
}

/*
 * Testy
 */

typedef unsigned long long ulonglong;
typedef long long longlong;
typedef long double longdouble;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

#define VARIABLES(type, value)	     \
  const type c_##type = value;       \
  type n_##type = c_##type;	     \
  type& r_##type = n_##type;	     \
  const type& cr_##type = c_##type;  \
  type* p_##type = &n_##type;	     \
  const type* cp_##type = &c_##type;

#define PRINT_TEST(var1, var2) \
  std::cout << "max((" << typeid(var1).name() << ")" << value(var1) << ", (" << typeid(var2).name() << ")" <<  value(var2) << " = (" << typeid(max(var1, var2)).name() << ")" << max(var1, var2) << std::endl; \
  assert(max(var1, var2) == value(var1) || max(var1, var2) == value(var2));

#define TEST_AUX(type1, type2)  \
  PRINT_TEST(type1, c_##type2)	\
  PRINT_TEST(type1, n_##type2)  \
  PRINT_TEST(type1, r_##type2)  \
  PRINT_TEST(type1, cr_##type2) \
  PRINT_TEST(type1, p_##type2)  \
  PRINT_TEST(type1, cp_##type2) \

#define TEST_ALL(type1, type2) \
  TEST_AUX(n_##type1, type2)   \
  TEST_AUX(c_##type1, type2)   \
  TEST_AUX(r_##type1, type2)   \
  TEST_AUX(cr_##type1, type2)  \
  TEST_AUX(p_##type1, type2)   \
  TEST_AUX(cp_##type1, type2)  \

#define TEST(type)            \
  TEST_ALL(type, longdouble); \
  TEST_ALL(type, double);     \
  TEST_ALL(type, float);      \
  TEST_ALL(type, ulonglong);  \
  TEST_ALL(type, int);        \
  TEST_ALL(type, uint);       \
  TEST_ALL(type, short);      \
  TEST_ALL(type, ushort);     \
  TEST_ALL(type, char);       \
  TEST_ALL(type, uchar);      \
  TEST_ALL(type, bool);

int main(int, char*[])
{
  VARIABLES(longdouble, std::numeric_limits<longdouble>::max());
  VARIABLES(double,     std::numeric_limits<double>::max());
  VARIABLES(float,      std::numeric_limits<float>::max());
  VARIABLES(ulonglong,  std::numeric_limits<ulonglong>::max());
  VARIABLES(int,        std::numeric_limits<int>::max());
  VARIABLES(uint,       std::numeric_limits<uint>::max());
  VARIABLES(short,      std::numeric_limits<short>::max());
  VARIABLES(ushort,     std::numeric_limits<ushort>::max());
  VARIABLES(char,       std::numeric_limits<char>::max());
  VARIABLES(uchar,      std::numeric_limits<uchar>::max());
  VARIABLES(bool,       std::numeric_limits<bool>::max());

  TEST(longdouble);
  TEST(double);
  TEST(float);
  TEST(ulonglong);
  TEST(int);
  TEST(uint);
  TEST(short);
  TEST(ushort);
  TEST(char);
  TEST(uchar);
  TEST(bool);
  
  return 0;
}
  
