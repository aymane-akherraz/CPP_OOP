#include <iostream>

using namespace std;

class DivideByZeroException : public exception {
public:
    const char* what() const throw() {
        return "Your input is not valid, you can't divide by zero.";
    }
};

void division(const int& numerator, const int& denominator) throw(DivideByZeroException)
{
	 if (denominator == 0) {
            throw DivideByZeroException();
        }
		cout << "Result: " << numerator / denominator << endl;
}

int main() {
    int numerator, denominator;
    cout << "Enter numerator: ";
    cin >> numerator;
    cout << "Enter denominator: ";
    cin >> denominator;
    try {
		division(numerator, denominator);
    }
    catch (const DivideByZeroException& ex) {
        cout << ex.what() << endl;
    }
    return 0;
}
