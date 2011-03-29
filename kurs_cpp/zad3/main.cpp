#include <iostream>
#include <exception>
using namespace std;

#include "date.h"

void unitTests()
{
}

void interactiveTest()
{
	try
	{
		int day, month;
		int year;
		cin >> day >> month >> year;

		Date d(day, month, year);
	}
	catch(const std::string& e)
	{
		cout << e << '\n';
	}
}

int main()
{
    // unitTests();
    interactiveTest();
    return 0;
}
