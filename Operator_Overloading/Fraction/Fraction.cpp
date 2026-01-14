#include <iostream>
#include <sstream>
#include "Fraction.hpp"

using namespace std;

int Fraction::LCM(int a, int b) {
    return a / GCD(a, b) * b;
}

int Fraction::GCD(int a, int b) {
	while (b) 
    {       
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

Fraction::Fraction() : numerator(0), denominator(1) {
};

Fraction::Fraction(int n) : numerator(n), denominator(1) {
};

Fraction::Fraction(int n,int d) : numerator(n), denominator(d) {
    if(denominator == 0)
        throw domain_error("bad fraction");
};

string Fraction::GetString(void) {
    ostringstream os;
    os << "[" << numerator << "/" << denominator << "]";
    return os.str();
}

double Fraction::GetValue(void) {
    return double(numerator) / double(denominator);
}

Fraction Fraction::operator!(void) {
    int gcd = GCD(numerator, denominator);
    return Fraction(numerator / gcd, denominator / gcd);
}

Fraction Fraction::operator+(Fraction arg) {
    int common_denom = LCM(denominator, arg.denominator);
    int numera = numerator * common_denom / denominator + 
             arg.numerator * common_denom / arg.denominator;
    Fraction f(numera, common_denom);
    return f;
}

Fraction Fraction::operator*(Fraction arg) {
    int numera = numerator * arg.numerator;
    int denomi = denominator * arg.denominator;
    Fraction f(numera, denomi);
    return !f;
}
Fraction Fraction::operator/(Fraction arg) {
    if(arg.numerator == 0)
        throw domain_error("division by zero");
    int numera = numerator * arg.denominator;
    int denomi = denominator * arg.numerator;
    Fraction f(numera, denomi);
    return !f;
}
Fraction& Fraction::operator+=(Fraction arg) {
    int common_denom = LCM(denominator, arg.denominator);
    int numera = numerator * common_denom / denominator + 
             arg.numerator * common_denom / arg.denominator;
    numerator   = numera;
    denominator = common_denom;
    return *this;

}

ostream& operator<< (ostream &ostr, Fraction &f) {
    return ostr << f.GetString();
}
