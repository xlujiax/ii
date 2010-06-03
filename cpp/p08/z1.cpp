#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <map>
using namespace std;

void store(string s, map<string, int>& dict)
{
  string::iterator new_end = remove_if(s.begin(),s.end(), not1(ptr_fun(::isalpha)));
  s.resize(new_end - s.begin());
  
  transform(s.begin(), s.end(), s.begin(), ::tolower);
  
  dict[s]++;
}

bool higher_word_count(pair<string, int> a, pair<string, int> b)
{
  return a.second > b.second;
}

void print(pair<string, int> p)
{
  cout << p.second << ' ' << p.first << endl;
}

bool empty_string(pair<string, int> p)
{
  return p.first.empty();
}

int main()
{
  map<string, int> dictionary;
  vector<pair<string, int> > word_count;

  for_each(istream_iterator<string>(cin), istream_iterator<string>(), bind2nd(ptr_fun(store), dictionary));
  
  word_count.reserve(dictionary.size());
  copy(dictionary.begin(), dictionary.end(), back_inserter(word_count));
  
  sort(word_count.begin(), word_count.end(), higher_word_count);
  
  vector<pair<string, int> >::iterator new_end = remove_if(word_count.begin(), word_count.end(), empty_string);
  word_count.resize(new_end - word_count.begin());
  
  for_each(word_count.begin(), word_count.end(), print);
  return 0;
}
