#pragma once

#include <iostream>

// Bignums implemented as single-linked list.
// Least significant digit is at the front.
struct digit
{
  char n;
  digit* next;
};

digit* buildbigint(unsigned int x);
void printbigint(std::ostream& os, const digit* big);
void deletebigint(digit* big);
digit* copy(const digit* lst);
void addto(const digit* from, digit*& to);
void subtractfrom(const digit* x, digit*& from);
digit* multiply(const digit* a, const digit* b);
int compare(const digit* a, const digit* b);
