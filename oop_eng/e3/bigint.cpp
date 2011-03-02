#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <cassert>

struct digit
{
  char n;
  digit* next;
};

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

void printbigint(const digit* big)
{
  std::vector<char> digits;
  while(big)
  {
    digits.push_back(big->n);
    big = big->next;
  }
  if(digits.empty())
    std::cout << '0' << '\n';
  else
  {
    for(std::vector<char>::reverse_iterator i = digits.rbegin(); i != digits.rend(); ++i)
    {
      std::cout << d2i(*i);
    }
    std::cout << '\n';
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

// moves foreward carry
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
  rm_leading_0s(result);
  return result;
}

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
  printbigint(factorial(690));
  
  return 0;
}
