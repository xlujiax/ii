#include <iostream>
#include <list>
#include <map>


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


std::map<std::string, unsigned int> frequencytable(std::list<std::string> &words)
{
  std::map<std::string, unsigned int> m;
  for(std::list<std::string>::iterator i = words.begin(); i != words.end(); ++i)
    m[*i]++;
  return m;
}

int main(int arc, char* argv[])
{
  std::list<std::string> words = readwords(std::cin);
  std::map<std::string, unsigned int> freq = frequencytable(words);

  for(std::map<std::string, unsigned int>::iterator i = freq.begin(); i != freq.end(); ++i)
  {
    std::cout << (*i).first << ' ' << (*i).second << '\n';
  }
  return 0;
}
