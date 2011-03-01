// This program is made by Maciej Pacut
#include <iostream>
#include <string>

int main( unsigned int nrargs, char* args [] )
{
  std::cout << "what is your name ? ";
  std::string name;
  std::cin >> name;

  std::cout << "good morning, " << name << "\n";
  return 0;
}

