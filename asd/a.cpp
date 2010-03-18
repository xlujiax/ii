// Maciej Pacut, 221082

#include <cstdio>
#include <map>
using namespace std;

// mapa z długości sznurków w ich liczność
typedef map<int, int, greater<int> > smap;
typedef smap::iterator siter;

int main()
{
  int n;
  scanf("%d", &n);

  smap ones;
  smap more;
  
  for(int i = 0; i < n; ++i)
  {
    int amount, len;
    scanf("%d %d", &len, &amount);

    if(amount == 1)
      ones[len] = 1;
    else
      more[len] = amount;
  }

  while(!more.empty())
  {
    siter longest = more.begin();
    int amount = (*longest).second;
    int len = (*longest).first;
    more.erase(longest);

    siter twice = ones.find(len*2);
    
    if(twice != ones.end())
    {
      more[len*2] = amount / 2 + 1;
      ones.erase(twice);
    }
    else
    {
      if(amount / 2 == 1)
	ones[len*2] = 1;
      else
	more[len*2] = amount / 2;
    }

    if(amount % 2 != 0)
    {
      ones[len] = 1;
      
    }
  }

  printf("%d\n",ones.size());
  
  return 0;
}
