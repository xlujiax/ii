#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>

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


int main(int argc, char* argv[])
{
  digit* d = buildbigint(182773087);
  printbigint(d);
  return 0;
}
