// Maciej Pacut, 221082

//#define NDEBUG

#include <cassert>
#include <iostream>
using namespace std;

static const int MAX_DATA = 10;//00000;
int arr[MAX_DATA];

int counter = 0;

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
}

void print_arr()
{
  cout << "[ ";
  for(int i = 0; i < MAX_DATA; ++i)
    if(arr[i])
    {
      cout << "(" << i << "," << arr[i] << ") ";
    }
  cout << "]" << endl;
}

int binary_ones(int n)
{
  int c = 0;
  while(n)
  {
    if(n % 2 != 0)
      ++c;
    n /= 2;
  }
  return c;
}

void insert(int len, int amount)
{
  print_arr();
  cout << "insert(" << len << ", " << amount << ")" << endl;
  if(len >= MAX_DATA)
  {
    insert(len/2,amount*2);
  }
  else
  {
    if(arr[len] != 0)
    {
      counter -= binary_ones(arr[len]);
      
      amount += arr[len];
      arr[len] = 0;
    }
    
    assert(arr[len] == 0);

    if(amount == 1)
    {
      ++counter;
      arr[len] = 1;
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
  }

  print_arr();

  cout << counter << endl;

  return 0;
}
