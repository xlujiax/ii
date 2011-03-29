#include <iostream>
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
  TabBit t(72);
  t.pisz(3, true);
  t.pisz(4, true);
  t.pisz(4, false);
  t.pisz(1, false);
  t.pisz(1, true);
  cout << t << endl;
}

int main(int argc, char* argv[])
{
  testZTresci();
  
  return 0;
}
