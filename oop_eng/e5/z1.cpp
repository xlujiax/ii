#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>

std::list<std::string> readwords(std::istream& stream)
{
  std::list<std::string> lst;
  std::string word;
  while(!stream.eof())
  {
    char c;
    stream.get(c);
    if(isalpha(c))
      word.push_back(c);
    else
    {
      if(!word.empty())
      {
	lst.push_back(word);
	word.clear();
      }
    }
  }
  return lst;
}

int main(int argc, char* argv[])
{
  std::list<std::string> lst = readwords(std::cin);
  std::copy(lst.begin(), lst.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
  return 0;
}
