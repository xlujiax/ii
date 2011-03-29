#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

#include <cassert>

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

void testWypisania()
{
  TabBit t(10);
  t[3] = true;
  cout << t << endl;
}

void testKopiowania()
{
  TabBit t1(10);
  TabBit t2(10);

  t1[3] = t1[4] = t1[7] = true;
  copy(t1.begin(), t1.end(), t2.begin());

  cout << t1 << endl;
  cout << t2 << endl;
}

void testRownosci()
{
  TabBit t1(10);
  TabBit t2(10);

  t1[3] = t1[4] = t1[7] = true;
  t2[7] = t2[3] = t2[4] = true;
  
  assert(equal(t1.begin(), t1.end(), t2.begin()));
}

void testNegacji()
{
  TabBit t(10);
  fill_n(t.begin(), 10, false);
  t[3] = t[4] = t[7] = true;
  cout << t << endl;
  cout << ~t << endl;
}

void test()
{
  //testWypisania();
  testRownosci();
  //testKopiowania();
  testNegacji();
}

int main(int argc, char* argv[])
{
  test();
  
  return 0;
}
