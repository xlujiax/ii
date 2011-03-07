#include "bignum.h"

bigunsigned::bigunsigned()
{
  d = 0;
}

bigunsigned::bigunsigned(unsigned int x)
{
  d = buildbigint(x);
}
