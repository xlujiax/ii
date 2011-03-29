#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm> // for lower_bound

class Date
{
public:
    const int day;
    const int month;
    const int year;
public:
	Date();
	Date(const int d, const int m, const int y);
	// domyœlny konstruktor kopiuj¹cy jest wystarczaj¹cy, gdy¿ obiekt ma trywialny destruktor

	friend std::ostream& operator<<(std::ostream&, const Date&);
	static int diff(const Date& from, const Date& to);
protected:
	bool przestepny() const;
private:
	void validate() const;
	int days_from_begining() const;
	static const int days_from_beg[2][13];
	static const int days_of_month[2][13];
};
