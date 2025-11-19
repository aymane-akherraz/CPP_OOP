#include <iostream>
#include <string>

using namespace std;

class Square
{
	// The side and area are private by default we don't need to use the private keyword here
	double    side;
	double    area;
public:
	Square(double side);
	void set_side(double side);
	double get_side() { return side; }
	double get_area() { return area; }
	void print(Square* square);
};

Square::Square(double side)
{
	this->side = side;
	this->area = side * side;
}

void Square::set_side(double side)
{
	if (side >= 0) {
		this->side = side;
		this->area = side * side;
	}
	else
		cout << "the side should be greater or equal zero\n";
}

void Square::print(Square* square)
{
	cout << "Square: side=" << square->get_side() << " area=" << square->get_area() << endl;

	// This also works because a member function of a class has full access to all private members of any object of the same class
	// cout << "Square: side=" << this->side << " area=" << square->area << endl;
}

int main()
{
	Square s(4);

	s.print(&s);

	s.set_side(2.0);
	s.print(&s);

	s.set_side(-33.0);
	s.print(&s);
	// we can also do this:
	// cout << "Side = " << s.get_side() << endl;
	// cout << "Area= " << s.get_area() << endl;
	return 0;
}
