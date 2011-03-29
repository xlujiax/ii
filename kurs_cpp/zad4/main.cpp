#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

#include "tabbit.h"

void testZTresci()
{
  TabBit t(72);
  t[0] = 1;
  t[71] = true;
  bool b = t[0];
  t[40] = b;
  t[36] = t[38] = t[71];
  cout<<t<<endl;
}

void test()
{
  TabBit t(10);
  t[3] = true;
  std::copy(t.begin(), t.end(), std::ostream_iterator<bool>(std::cout, ""));
  std::cout << std::endl;
  std::cout << t << std::endl;
}

int main(int argc, char* argv[])
{
  test();
  
  return 0;
}
