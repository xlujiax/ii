// Maciej Pacut, 221082

#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;

static const int MAX_DATA = 1000000 * 63;

bool arr[MAX_DATA];
int counter = 0;

/*
unsigned int count_ones()
{
  unsigned int count = 0;
  for(int i = 0; i < MAX_DATA; ++i)
    if(arr[i])
      count ++;
  return count;
}

void print()
{
  cout << "[ ";
  for(int i = 0; i < MAX_DATA; ++i)
    if(arr[i])
      cout << i << " ";
  cout << "]" << endl;
}

void binary(int n)
{
  while(n != 0)
  {
    if(n % 2 != 0)
      cout << 1;
    else
      cout << 0;
      
    n = n / 2;
  }
  cout << endl;
}*/

void insert(int len, int amount)
{
  if(arr[len])
  {
    amount++;
    arr[len] = false;
    --counter;
  }

  if(amount == 1)
  {
    arr[len] = 1;
    ++counter;
  }
  else
  {
    int inserter = len;
    while(amount != 0)
    {
      if(amount % 2 != 0)
      {
	insert(inserter, 1);
      }
      
      amount = amount / 2;
      inserter *= 2;
    }
  }
}

int main()
{
  ios_base::sync_with_stdio(0);
  
  int n;
  cin >> n;

  for(int i = 0; i < n; ++i)
  {
    int amount, len;
    cin >> len >> amount;
    insert(len, amount);

    //cout << "insert " << len << " " << amount << " = ";
    //binary(amount);
    //print();
  }

  cout << counter << endl;

  return 0;
}
