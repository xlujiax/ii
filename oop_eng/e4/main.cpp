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

int main(int argc, char* argv[])
{
  memory_leak_test();
  
  return 0;
}
