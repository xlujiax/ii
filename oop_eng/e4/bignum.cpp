#include "bignum.h"

bigunsigned::bigunsigned()
{
  d = 0;
}

bigunsigned::bigunsigned(unsigned int x)
{
  d = buildbigint(x);
}

bigunsigned::bigunsigned(const bigunsigned& b)
{
  d = copy(b.d);
}

bigunsigned::~bigunsigned()
{
  deletebigint(d);
}

bigunsigned& bigunsigned::operator = (const bigunsigned& b)
{
  if(this != &b)
  {
    deletebigint(d);
    d = copy(b.d);
  }
  return *this;
}
