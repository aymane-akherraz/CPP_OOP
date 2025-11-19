#include <iostream>
using namespace std;

class AdHocSquare
{
public:
	AdHocSquare(double side);
	void set_side(double side);
	double get_area() { return side * side; }
private:
	double    side;
};

AdHocSquare::AdHocSquare(double side)
{
	this->side = side;
}

void AdHocSquare::set_side(double new_side)
{
	if (new_side >= 0)
		this->side = new_side;
	else
        cout << "the side should be greater or equal zero\n";
}

class LazySquare
{
public:
	LazySquare(double side);
	void set_side(double side);
	void set_area(double area);
	void set_flag(bool val);
	double get_area();
private:
	double    side;
	double    area;
	bool      side_changed;
};

LazySquare::LazySquare(double side)
{
	this->side = side;
	this->area = side * side;
	this->side_changed = false;
}

void LazySquare::set_side(double new_side)
{   
	if (new_side >= 0) {
		if (new_side != this->side) {
	 		this->side = new_side;
			set_flag(true);
		}
	}
	else
        cout << "the side should be greater or equal zero\n";
}

void LazySquare::set_area(double new_area)
{
	this->area = new_area;
}

void LazySquare::set_flag(bool new_val)
{
    this->side_changed = new_val;
}

double LazySquare::get_area()
{
	if (this->side_changed) {
		set_area(this->side * this->side);
		set_flag(false);
	}
	return this->area;
}

int main()
{
	AdHocSquare s1(4);
	std::cout << "Square area=" << s1.get_area() << std::endl;

	LazySquare s2(6);
	std::cout << "Square area=" << s2.get_area() << std::endl;

	s2.set_side(5);
	std::cout << "Square area=" << s2.get_area() << std::endl;
	return 0;
}
