#include <iostream>
#include <cstdlib>
#include "bignum.h"

void memory_leak_test()
{
  for(int i = 0; i < 10000000; ++i)
  {
    bigunsigned b(rand() % 10000);
    b = b;
    bigunsigned c(rand() % 10000);
    c = b;
    bigunsigned d = b;
    d = d;
  }
}

bigunsigned factorial(int n)
{
  bigunsigned res(1);
  for(int i = 2; i <= n; ++i)
  {
    bigunsigned big_i(i);
    res = res * big_i;
  }
  return res;
}

bigunsigned power(int base, int exp)
{
  bigunsigned big_base(base);
  bigunsigned ret(1);
  for(int i = 0; i < exp; ++i)
    ret = ret * big_base;
  return ret;
}

void computation_test()
{
  std::cout << factorial(69) << '\n';
  std::cout << power(2, 100) << '\n';
}

void operators_test()
{
  bigunsigned b(45);
  std::cout << b-- << '\n';
  std::cout << b << '\n';

  bigunsigned c(45);
  std::cout << ++c << '\n';
  std::cout << c << '\n';
}

int main(int argc, char* argv[])
{
  //memory_leak_test();
  computation_test();
  //operators_test();
  
  return 0;
}
