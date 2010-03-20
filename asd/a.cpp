// Maciej Pacut, 221082

#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;

// mapa z długości sznurków w ich liczność
typedef map<int, int> smap;
typedef smap::iterator siter;

int main()
{
  ios_base::sync_with_stdio(0);
  
  int n;
  cin >> n;

  smap str;
  
  for(int i = 0; i < n; ++i)
  {
    int amount, len;
    cin >> len >> amount;
    str[len] = amount;
  }

  int counter = 0;

  while(!str.empty())
  {
    siter shortest = str.begin();
    int amount = (*shortest).second;
    int len = (*shortest).first;

    str.erase(shortest);

    if(amount == 1)
    {
      counter ++;
    }
    else
    {
      int insert = len;
      while(amount != 0)
      {
	if(amount % 2 != 0)
	  str[insert]++;
	
	amount = amount / 2;
	insert *= 2;
      }
    }
  }
  cout << counter << endl;

  return 0;
}
