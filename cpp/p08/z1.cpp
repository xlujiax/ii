#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct word
{
  string& s;
  string::iterator b;
  word(string& S) : s(S), b(s.begin()) {}
  string operator()()
  {
    string::iterator punc = find_if(find_if(b, s.end(), ptr_fun(::isalpha)), s.end(), not1(ptr_fun(::isalpha)));

    string ret(b, punc);

    b = punc;
    
    return ret;
  }
};

void store_aux(string s, map<string, int>* dict)
{
  transform(s.begin(), s.end(), s.begin(), ::tolower);
  string::iterator new_end = remove_if(s.begin(), s.end(), not1(ptr_fun(::isalpha)));
  (*dict)[string(s.begin(), new_end)]++;
}

void store(string s, map<string, int>* dict)
{
  vector<string> vs;

  int punc_left = count_if(s.begin(),s.end(), not1(ptr_fun(::isalpha)));
  vs.reserve(punc_left);
  generate_n(back_inserter(vs),punc_left + 1, word(s));

  for_each(vs.begin(), vs.end(), bind2nd(ptr_fun(store_aux), dict));
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

  for_each(istream_iterator<string>(cin), istream_iterator<string>(), bind2nd(ptr_fun(store), &dictionary));
  
  word_count.reserve(dictionary.size());
  copy(dictionary.begin(), dictionary.end(), back_inserter(word_count));
  
  sort(word_count.begin(), word_count.end(), higher_word_count);
  
  vector<pair<string, int> >::iterator new_end = remove_if(word_count.begin(), word_count.end(), empty_string);
  word_count.resize(new_end - word_count.begin());
  
  for_each(word_count.begin(), word_count.end(), print);
  return 0;
}
