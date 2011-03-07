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

void computation_test()
{
  std::cout << factorial(69) << '\n';
}

int main(int argc, char* argv[])
{
  //memory_leak_test();
  computation_test();
  
  return 0;
}
