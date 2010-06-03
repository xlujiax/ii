#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <iostream>
#include <locale>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

// analiza zlozonosci

// n - liczba slow
// m - liczba znakow w slowie
// M - liczba znakow w slowie + interpunkcja

map<string, int> words;
vector<pair<string, int> > words2;

bool not_alphanumeric(char c)
{
  return !isalpha(c);
}

char lowercase(char c)
{
  return tolower(c);
}

// czas O(M)
// pamiec O(1)
string remove_punctation(string s)
{
  string::iterator new_end = remove_copy_if(s.begin(),s.end(),s.begin(), not_alphanumeric);
  s.resize(new_end - s.begin());
  return s;
}

string make_lowercase(string s)
{
  string::iterator new_end = transform(s.begin(),s.end(),s.begin(), lowercase);
  return s;
}

void add(string s)
{
  string no_punctation = remove_punctation(s);
  string lc = make_lowercase(no_punctation);
  words[lc]++;
}

bool cnt(pair<string, int> a, pair<string, int> b)
{
  return a.second > b.second;
}

void print(pair<string, int> p)
{
  cout << p.second << ' ' << p.first << endl;
}

int main()
{
  for_each(istream_iterator<string>(cin), istream_iterator<string>(), add);
  words2.reserve(words.size());
  copy(words.begin(), words.end(), back_inserter(words2));
  sort(words2.begin(), words2.end(), cnt);
  for_each(words2.begin(), words2.end(), print);
  return 0;
}
