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
	Fraction plus(Fraction that);
	Fraction minus(Fraction that);
	Fraction times(Fraction that);
	Fraction by(Fraction that);
private:
	int numerator;
	int denominator;
	void reduce();
};

void Fraction::reduce()
{
	int r, a, b;

	a = numerator;
	b = denominator;
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


Fraction Fraction::times(Fraction that)
{
	int num = this->numerator * that.numerator;
	int den = this->denominator * that.denominator;
	Fraction res = Fraction(num, den);
	res.reduce();
	return res;
}

Fraction Fraction::by(Fraction that)
{
    int num = this->numerator * that.denominator;
    int den = this->denominator * that.numerator;
    Fraction res = Fraction(num, den);
    res.reduce();
    return res;
}

Fraction Fraction::plus(Fraction that)
{
	int num = (this->numerator * that.denominator) + (that.numerator * this->denominator);
    int den = this->denominator * that.denominator;
    Fraction res = Fraction(num, den);
    res.reduce();
    return res;
}

Fraction Fraction::minus(Fraction that)
{
	int num = (this->numerator * that.denominator) - (that.numerator * this->denominator);
    int den = this->denominator * that.denominator;
    Fraction res = Fraction(num, den);
    res.reduce();
    return res;
}

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
	cout << a.toString() << " + " << b.toString() << " = " << a.plus(b).toString() << endl;
	cout << a.toString() << " - " << b.toString() << " = " << a.minus(b).toString() << endl;
	cout << a.toString() << " * " << b.toString() << " = " << a.times(b).toString() << endl;
	cout << a.toString() << " / " << b.toString() << " = " << a.by(b).toString() << endl;
	return 0;
}
