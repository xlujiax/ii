#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <cassert>

#include "bigint.h"

// Conversion between integer and char representation of digit.
// Digits can temporarily be others then 0,1,2,3,4,5,6,7,8,9,
// because of addition, subtraction and multiplication.
// Minimal value is -9 as result of 0 - 9.
// Maximal value is 81 as result of 9 * 9.
// Therefore, 0 is represented as binary 10 in char.
char i2d(int i)
{
  return i + 10;
}

int d2i(char d)
{
  return d - 10;
}


std::pair<unsigned int, char> deconstruct(const unsigned int x)
{
  return std::make_pair(x / 10, i2d(x % 10));
}

digit* buildbigint(unsigned int x)
{
  if(x == 0)
    return 0;

  std::pair<unsigned int, char> x_deconstructed = deconstruct(x);
  digit* big = new digit;
  big->n = x_deconstructed.second;
  big->next = buildbigint(x_deconstructed.first);
  return big;
}

// Printing bignum using additional O(n) memory.
void printbigint(std::ostream& os, const digit* big)
{
  std::vector<char> digits;
  while(big)
  {
    digits.push_back(big->n);
    big = big->next;
  }
  if(digits.empty())
    os << '0';
  else
  {
    for(std::vector<char>::reverse_iterator i = digits.rbegin(); i != digits.rend(); ++i)
    {
      os << d2i(*i);
    }
  }
}

void deletebigint(digit* big)
{
  while(big)
  {
    digit* temp = big;
    big = big->next;
    delete temp;
  }
}

// Moves carry foreward.
// This function is more general then fix_under_0 because
// fix_over_9 is used in addition as well as in multiplication,
// where temporarily excessive values can range up to 9*9 = 81
// with carry = 8
void fix_over_9(digit* big)
{
  while(big)
  {
    if(d2i(big->n) > 9)
    {
      int carry = d2i(big->n) / 10;
      big->n = i2d(d2i(big->n) % 10);

      assert(carry > 0);

      if(big->next)
	big->next->n = i2d(d2i(big->next->n) + carry);
      else
      {
	big->next = new digit;
	big->next->next = 0;
	big->next->n = i2d(carry);
      }
    }
      
    big = big->next;
  }
}

// Creates copy of bignum by adding elements to the end of the new bignum.
// Complexity O(n) is obtained by keeping pointer to last digit of new bignum.
digit* copy(const digit* lst)
{
  if(!lst) return 0;

  // list not empty; creating new list and copying first element of original list into it
  digit* new_lst = new digit;
  new_lst->n = lst->n;

  // iteration from second element of original list
  lst = lst->next;

  // iteration creates new cells and attaches them to end of new list
  digit* last_cell = new_lst;
  while(lst)
  {
    digit* new_cell = new digit;
    new_cell->n = lst->n;
    last_cell->next = new_cell;
    last_cell = new_cell; // actualize last cell as we attached new cell in line one above
    lst = lst->next;
  }
  
  last_cell->next = 0;
  return new_lst;
}

// Append shares 'end' and second part of newly created bignum
void append(digit*& begin, digit* end)
{
  if(!begin)
    begin = end;
  else
  {
    digit* begin_iter = begin;
    while(begin_iter->next)
    {
      begin_iter = begin_iter->next;
    }
    begin_iter->next = end;
  }
}

// Addition is done in two steps.
// First one adds corresponding digits, where result of addition
// can exceed 9. Second step moves carry foreward to obtain
// digits in 0..9
void addto(const digit* from, digit*& to)
{
  digit* to_iter = to;
  while(from && to_iter)
  {
    to_iter->n = i2d(d2i(to_iter->n) + d2i(from->n));
    to_iter = to_iter->next;
    from = from->next;
  }

  // from is longer then to
  if(from)
  {
    // copy rest of 'from' to 'to'
    digit* rest_of_from = copy(from);
    append(to, rest_of_from);
  }

  fix_over_9(to);
}

// Moves negative carry foreward
void fix_under_0(digit* big)
{
  while(big)
  {
    if(d2i(big->n) < 0)
    {
      big->n = i2d(10 + d2i(big->n));

      assert(big->next);

      big->next->n--;
    }
      
    big = big->next;
  }
}

// Auxilary function for subtractfrom
void rm_leading_0s(digit*& big)
{
  digit* last_non_0 = 0;
  digit* big_iter = big;
  while(big_iter)
  {
    if(big_iter->n != i2d(0))
      last_non_0 = big_iter;
    big_iter = big_iter->next;
  }
  
  if(last_non_0 == 0)
  {
    // no digits other then 0
    big = 0;
  }
  else
  {
    if(last_non_0->next)
    {
      deletebigint(last_non_0->next);
    }
    last_non_0->next = 0;
  }
}

// Subtraction is done in three steps; for first 2 see addto.
// Third step is removing leading zeros.
void subtractfrom(const digit* x, digit*& from)
{
  digit* from_iter = from;
  while(x && from_iter)
  {
    from_iter->n = i2d(d2i(from_iter->n) - d2i(x->n));
    x = x->next;
    from_iter = from_iter->next;
  }

  if(x)
  {
    from = 0;
  }
  else
  {
    fix_under_0(from);
    rm_leading_0s(from);
  }
}

// Auxilary function for multiply.
// Performs one step of full multiplication.
void multiply_by_digit(digit* a, int x)
{
  digit* original_a = a;
  while(a)
  {
    a->n = i2d(d2i(a->n) * x);
    a = a->next;
  }
  fix_over_9(original_a);
}

// Full multiplication.
// For every digit d in 'a' b is multiplied by d.
// Final result is obtained by addition of all results of multiplications with proper offset.
digit* multiply(const digit* a, const digit* b)
{
  digit* result = 0;
  int offset = 0;
  while(a)
  {
    if(a->n != i2d(0))
    {
      digit* row = copy(b);
      multiply_by_digit(row, d2i(a->n));
      for(int i = 0; i < offset; ++i)
      {
	digit* new_row = new digit;
	new_row->next = row;
	new_row->n = i2d(0);
	row = new_row;
      }
      addto(row, result);
      deletebigint(row);
    }
    ++offset;
    a = a->next;
  }
  // needed when a or b is 0
  rm_leading_0s(result);
  return result;
}

