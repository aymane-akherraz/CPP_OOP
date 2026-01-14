#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Fraction{
public:
	Fraction(int numerator, int denominator);
	string toString();
	double toDouble();
private:
	int numerator;
	int denominator;
};


Fraction::Fraction(int numerator, int denominator) : numerator(numerator),
					denominator(denominator) {}

double Fraction::toDouble()
{
	return ((numerator / denominator) + (static_cast<double>(numerator % denominator) / denominator));
}

string Fraction::toString()
{
	std::ostringstream buffer;
	int q = numerator / denominator;
	int r = numerator % denominator;
	if (q)
		buffer << q;
	else
		buffer << numerator << "/" << denominator;
	if (r && q)
		buffer << " " << r << "/" << (denominator < 0? -denominator : denominator);
	return buffer.str();
}

int show_usage()
{
	cout << "Input format: [numerator] / [denominator]" << endl;
	return 0;
}

int main(void) {
	int num, den;
	std::string input;
	std::getline(cin, input);
	std::istringstream iss(input);

	iss >> num;
	if (!iss.fail())
	{
		char div;
		iss >> div;
		if (!iss.fail())
		{
			iss >> den;
			if (iss.fail() || !iss.eof())
				return show_usage();
		}
		else
			return show_usage();
	}
	else
		return show_usage();
	Fraction fraction(num, den);
	
	cout << fraction.toString() << " is " << fraction.toDouble() << " in decimal" << endl;
	return 0;
}
