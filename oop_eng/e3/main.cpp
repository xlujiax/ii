#include "bigint.h"
#include <iostream>

digit* factorial(int n)
{
  digit* res = buildbigint(1);
  for(int i = 2; i <= n; ++i)
  {
    digit* big_i = buildbigint(i);
    digit* original_res = res;
    res = multiply(res, big_i);
    deletebigint(original_res);
    deletebigint(big_i);
  }
  return res;
}

int main(int argc, char* argv[])
{
  std::cout << "69! is ";
  printbigint(factorial(69));
  
  return 0;
}
