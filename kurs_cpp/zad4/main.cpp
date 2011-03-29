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

void testKopiowania()
{
  TabBit t1(10);
  TabBit t2(10);

  t1[3] = t1[4] = t1[7] = true;
  copy(t1.begin(), t1.end(), t2.begin());

  assert(equal(t1.begin(), t1.end(), t2.begin()));
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
  TabBit falses(10);
  fill_n(falses.begin(), 10, false);

  TabBit trues(10);
  fill_n(trues.begin(), 10, true);

  assert(equal(
      falses.begin(), falses.end(), (~trues).begin()
));
}

void testPodwojnejNegacji()
{
  TabBit t(10);
  fill_n(t.begin(), 10, false);
  t[3] = t[4] = t[7] = true;

  TabBit negated = ~(~t);
  assert(equal(t.begin(), t.end(), negated.begin()));
}

void testOr()
{
  TabBit t1(3);
  TabBit t2(3);

  t1[1] = true;
  t2[1] = true;
  t1[0] = true;
  t2[2] = true;

  TabBit trues(3);
  fill_n(trues.begin(), 3, true);

  assert(equal(trues.begin(), trues.end(),
      (t1 | t2).begin()));
}

void testAnd()
{
  TabBit t1(3);
  TabBit t2(3);

  t1[1] = true;
  t2[1] = true;
  t1[0] = true;
  t2[2] = true;

  TabBit result(3);
  result[0] = false;
  result[1] = true;
  result[2] = false;
  
  assert(equal(result.begin(), result.end(),
      (t1 & t2).begin()));
}

void testXor()
{
  TabBit t1(3);
  TabBit t2(3);

  t1[1] = true;
  t2[1] = true;
  t1[0] = true;
  t2[2] = true;

  TabBit result(3);
  result[0] = true;
  result[1] = false;
  result[2] = true;
  
  assert(equal(result.begin(), result.end(),
      (t1 ^ t2).begin()));
}

void testOperatoryModyfikujace()
{
  TabBit t1(3);
  TabBit t2(3);
  
  t1[1] = true;
  t2[1] = true;
  t1[0] = true;
  t2[2] = true;

  t1 &= t2;
  
  TabBit result(3);
  result[0] = false;
  result[1] = true;
  result[2] = false;
  
  assert(equal(result.begin(), result.end(),
      t1.begin()));
}

void test()
{
  testRownosci();
  testKopiowania();
  testNegacji();
  testPodwojnejNegacji();
  testOr();
  testAnd();
  testXor();
  testOperatoryModyfikujace();

  cout << "Wszystkie testy zakonczone powodzeniem." << endl;
}

int main(int argc, char* argv[])
{
  test();
  
  return 0;
}
