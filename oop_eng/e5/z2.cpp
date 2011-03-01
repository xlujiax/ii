#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>

char replaceuppercase( char c )
{
  return tolower(c);
}

void replaceuppercase( std::string& s )
{
  for(std::string::iterator i = s.begin(); i != s.end(); ++i)
    *i = replaceuppercase(*i);
}

void replaceuppercase( std::list< std::string > & words )
{
  for(std::list<std::string>::iterator i = words.begin(); i != words.end(); ++i)
    replaceuppercase(*i);
}


int main(int argc, char* argv[])
{
  std::list<std::string> lst;
  lst.push_back("Ala's Cat is Bink.");
  lst.push_back("There is no path TO FOLLOW!");
  lst.push_back("Aa3#4$Bb");
  replaceuppercase(lst);

  std::copy(lst.begin(), lst.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
  
  return 0;
}
