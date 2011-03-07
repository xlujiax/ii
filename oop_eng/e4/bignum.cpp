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

bigunsigned bigunsigned::operator+(const bigunsigned& x) const
{
  bigunsigned b(0);
  addto(x.d, b.d);
  return b;
}
bigunsigned bigunsigned::operator-(const bigunsigned& x) const
{
  bigunsigned b(0);
  subtractfrom(x.d, b.d);
  return b;
}
bigunsigned bigunsigned::operator*(const bigunsigned& x) const
{
  bigunsigned b;
  b.d = multiply(d, x.d);
  return b;
}

bigunsigned& bigunsigned::operator++() //prefix
{
  digit* one = buildbigint(1);
  addto(one, d);
  deletebigint(one);
  return *this;
}
bigunsigned& bigunsigned::operator--() //prefix
{
  digit* one = buildbigint(1);
  subtractfrom(one, d);
  deletebigint(one);
  return *this;
}
bigunsigned bigunsigned::operator++(int unused) //postfix
{
  bigunsigned temp = *this;
  digit* one = buildbigint(1);
  addto(one, d);
  deletebigint(one);
  return temp;
}
bigunsigned bigunsigned::operator--(int unused) //postfix
{
  bigunsigned temp = *this;
  digit* one = buildbigint(1);
  subtractfrom(one, d);
  deletebigint(one);
  return temp;
}


std::ostream& operator << ( std::ostream& os, const bigunsigned &x)
{
  printbigint(os, x.d);
  return os;
}
