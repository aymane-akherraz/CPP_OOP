#include <iostream>
#include <stdexcept>

using namespace std;

class AreaException : public runtime_error
{
public:
	AreaException(const char * message): runtime_error(message){}
};

float square_area(float& a) throw (AreaException)
{
	if (a < 0)
		throw AreaException("Your input is not valid, area can't be negative.");
	return a * a;
}

float rectangle_area(float& a, float& b) throw (AreaException)
{
	if (a < 0 || b < 0)
		throw AreaException("Your input is not valid, area can't be negative.");
	return a * b;
}

int main(void) {
	float a, b;
	cin >> a;
	cin >> b;
	try
	{
		float rsquare = square_area(a);
		float rrectangle = rectangle_area(a,b);
		cout << "Square area: " << rsquare << endl;
		cout << "Rectangle area: " << rrectangle << endl;
	}
	catch (const AreaException& ex) {
		cout << ex.what() << endl;
	}
	return 0;
}
