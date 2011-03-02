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

std::pair<unsigned int, char> deconstruct(const unsigned int x)
{
  return std::make_pair(x / 10, (x % 10) + '0');
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
    std::copy(digits.rbegin(), digits.rend(), std::ostream_iterator<char>(std::cout, ""));
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

char i2d(int i)
{
  return i + '0';
}

int d2i(char d)
{
  return d - '0';
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

void append(digit* begin, digit* end)
{
  assert(begin);
  
  while(begin->next)
  {
    begin = begin->next;
  }
  begin->next = end;
}

void addto(const digit* from, digit* to)
{
  digit* original_to = to;
  while(from && to)
  {
    to->n = i2d(d2i(to->n) + d2i(from->n));
    to = to->next;
    from = from->next;
  }

  // from is longer then to
  if(from)
  {
    // copy rest of 'from' to 'to'
    digit* rest_of_from = copy(from);
    append(original_to, rest_of_from);
  }

  fix_over_9(original_to);
}

int main(int argc, char* argv[])
{
  digit* a = buildbigint(119);
  digit* b = buildbigint(3333333);
  printbigint(a);
  printbigint(b);
  addto(a, b);
  printbigint(a);
  printbigint(b);

  return 0;
}
