#include <iostream>
#include <sstream>
#include <iomanip> 
#include <cmath>

using namespace std;

class Point2D {
public:
	Point2D(double x, double y);
	Point2D();
	string toString();
	double toDouble();
	double distanceTo(Point2D that);
private:
	double x;
	double y;
};

Point2D::Point2D(double x, double y) : x(x), y(y) {}
Point2D::Point2D() : x(0), y(0) {}


double Point2D::distanceTo(Point2D that)
{
	return sqrt(pow((that.x - this->x), 2) + pow((that.y - this->y), 2));
}

int show_usage()
{
	cout << "Point coordinates format: x y" << endl;
	return 0;
}

int main(void) {
	double x, y;
	int i = 0;
	std::string input;
	Point2D a, b;
	while (i < 2)
	{
		if (i == 0)
			cout << "Enter first point coordinates: ";
		else
			cout << "Enter second point coordinates: ";
		getline(cin, input);
		istringstream iss(input);

		iss >> x;
		if (!iss.fail())
		{
			iss >> y;
			if (iss.fail() || !iss.eof())
				return show_usage();
		}
		else
			return show_usage();
		if (i == 0)
			a = Point2D(x, y);
		else
			b = Point2D(x, y);
		i++;
	}
	cout << fixed << setprecision(7) << a.distanceTo(b) << endl;
	return 0;
}
