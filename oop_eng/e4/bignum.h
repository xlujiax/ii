#pragma once

struct digit
{
  char n;
  digit* next;
};

class bigunsigned
{
  digit* d;
 public:
  bigunsigned();
};

