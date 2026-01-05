#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Fraction{
public:
	Fraction(int numerator, int denominator);
	Fraction();
	string toString();
	double toDouble();
	bool isGreaterThan(Fraction that);
	bool isLessThan(Fraction that);
	bool isEqual(Fraction that);
private:
	int numerator;
	int denominator;
	void reduce();
};

bool Fraction::isGreaterThan(Fraction that)
{
	return (this->toDouble() > that.toDouble());
}

bool Fraction::isLessThan(Fraction that)
{
	return (this->toDouble() < that.toDouble());
}

bool Fraction::isEqual(Fraction that)
{
	return (this->toDouble() == that.toDouble());
}

void Fraction::reduce()
{
	int r, a, b;

	a = abs(numerator);
	b = abs(denominator);
	while (a)
	{
		r = b % a;
		b = a;
		a = r;
	}
	numerator /= b;
	denominator /= b;
}

Fraction::Fraction() : numerator(0), denominator(0) {}

Fraction::Fraction(int numerator, int denominator)
		: numerator(numerator), denominator(denominator) {}

double Fraction::toDouble()
{
	return (static_cast<double>(numerator) / denominator);
}

string Fraction::toString()
{
	std::ostringstream buffer;

	this->reduce();
	int q = numerator / denominator;
	int r = numerator % denominator;
	if (q)
		buffer << q;
	else
		buffer << numerator << "/" << denominator;
	if (r && q)
		buffer << " " << r << "/" << abs(denominator);
	return buffer.str();
}

int show_usage()
{
	cout << "Fractional number format: [numerator] / [denominator]" << endl;
	return 0;
}

int main(void) {
	int num, den, i = 0;
	std::string input;
	Fraction a, b;
	while (i < 2)
	{
		if (i == 0)
			cout << "Enter first Fractional number: ";
		else
			cout << "Enter second Fractional number: ";
		getline(cin, input);
		istringstream iss(input);

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
		if (i == 0)
			a = Fraction(num, den);
		else
			b = Fraction(num, den);
		i++;
	}
	if (a.isGreaterThan(b))
		cout << a.toString() << " > " << b.toString() << endl;
	else if (a.isLessThan(b))
		cout << a.toString() << " < " << b.toString() << endl;
	else
		cout << a.toString() << " == " << b.toString() << endl;
	return 0;
}
