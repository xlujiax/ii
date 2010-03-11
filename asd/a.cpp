// Maciej Pacut, 221082

#include <iostream>
#include <map>
using namespace std;

// mapa z długości sznurków w ich liczność
typedef map<int, int, greater<int> > smap;
typedef smap::iterator siter;

int main()
{
  ios_base::sync_with_stdio(false);

  int n; cin >> n;

  smap ones;
  smap more;
  
  for(int i = 0; i < n; ++i)
  {
    int amount, len;
    cin >> len >> amount;
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

    /*
    cout << len << ' ' << amount << ' ' << more.size();

    cout << " [ ";
    for(siter i = ones.begin(); i != ones.end(); ++i)
      cout << (*i).first << ' ';
    cout << "]";
    
    cout << " { ";
    for(siter i = more.begin(); i != more.end(); ++i)
      cout << (*i).first << "(" << (*i).second << ") ";
    cout << "}" << endl;
    */
    
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

  cout << ones.size() << endl;
  
  return 0;
}
