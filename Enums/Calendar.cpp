#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

class Calendar
{
	int day;
	int month;
	int year;
public:
	void print();
	int days_of_year();
	Calendar(int d, int m, int y);
	int days_since_1970(int year);
	enum weekday {
		THURSTADY, FRIDAY, SATURDAY,
		SUNDAY, MONDAY, TUESDAY, WEDNESDAY
	};
	enum Month {
		JANUARY, FEBRUARY, MARCH, APRIL,
		MAY, JUNE, JULY, AUGUST, SEPTEMBER,
		OCTOBER, NOVEMBER, DECEMBER 
	};
};

Calendar::Calendar(int d, int m, int y)
{
	if (y < 1970)
		throw runtime_error("Please Enter a year greater or equal to 1970");
	year = y;
	if (d > 0 && d < 32)
		day = d;
	else
		throw runtime_error("Invalid day!");
	if (m > 0 && m < 13)
		month = m - 1;
	else
		throw runtime_error("Invalid month!");
}

static bool is_leap(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int Calendar::days_of_year() {
	int days = 0;
	int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	for (int m = 0; m < month; m++)
	{
		if (is_leap(year) && m == Calendar::FEBRUARY)
			days += months[m] + 1;
		else
			days += months[m];
	}
	days += day - 1;
	return (days);
}

int Calendar::days_since_1970(int year)
{
	size_t days_passed = 0;
	for (int y = 1970; y < year; y++)
	{
		if (is_leap(y))
			days_passed += 366;
		else
			days_passed += 365;
	}
	days_passed += days_of_year();
	return days_passed;
}

Calendar::weekday weekday_from_days(int days_passed)
{
    return static_cast<Calendar::weekday>(days_passed % 7);
}

const char* toString(int m)
{
    static const char* months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };
    return months[m];
}

const char* toString(Calendar::weekday d)
{
    static const char* weekdays[] = {
        "Thursday", "Friday", "Saturday",
        "Sunday", "Monday", "Tuesday", "Wednesday"
    };
    return weekdays[d];
}

void Calendar::print()
{
	int days_passed = days_since_1970(year);
	Calendar::weekday weekday = weekday_from_days(days_passed);
	cout << day << " " << toString(month) << " " << year
		 << " - " << toString(weekday) << " - " << days_passed
		 << " days since 1st January 1970" <<  endl;
}

int main()
{
	string line;
	cout << "Enter day (1-31):\n";
	if (getline(cin, line))
	{
		int day;
		istringstream iss(line);
		if (iss >> day)
		{
			cout << "Enter month (1-12):\n";
			if (getline(cin, line))
			{
				int month;
		        istringstream iss(line);
				if (iss >> month)
				{
					cout << "Enter year (1970-now):\n";
					if (getline(cin, line))
		            {
        		        int year;
	                	istringstream iss(line);
		                if (iss >> year)
    		            {
							Calendar c = Calendar(day, month, year);
							c.print();
						}
					}
				}
			}
		}
	}
}
