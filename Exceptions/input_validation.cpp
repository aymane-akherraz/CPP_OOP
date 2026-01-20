#include <iostream>

using namespace std;
const int DivideByZero = 111;

float internaldiv(float arg1, float arg2) throw(int)
{
	if (arg2 == 0.0)
		throw DivideByZero;
	return arg1 / arg2;
}

float div(float arg1, float arg2) throw(int) {
	try {
		return internaldiv(arg1, arg2);
	}
	catch (int& ex) {
		throw ex;
	}
}

int main(void) {
	float r, a, b;
	while (cin >> a) {
		cin >> b;
		try {
			r = div(a, b);
			cout << r << endl;
		}
		catch (int& ex) {
			if (ex == DivideByZero)
				cout << "Your input is not valid. You can't divide by zero." << endl;
		}
	}
	return 0;
}
