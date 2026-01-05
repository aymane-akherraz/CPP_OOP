#include <iostream>
#include <sstream>

using namespace std;

class Point2D{
public:
	Point2D(double x, double y);
	Point2D();
	string toString();
	double get_X();
	double get_Y();
private:
	double x;
	double y;
};

class Line2D{
public:
	Line2D(double slope, double y_intercept);
	Line2D(Point2D pointA, Point2D pointB);
	string toString();
	bool contains(Point2D point);
private:
	double slope;
	double y_intercept;
};

double Point2D::get_X()
{
	return x;
}

double Point2D::get_Y()
{
	return y;
}

Point2D::Point2D(double x, double y) : x(x), y(y) {}
Point2D::Point2D() : x(0), y(0) {}

Line2D::Line2D(Point2D pointA, Point2D pointB)
{
	slope = (pointB.get_Y() - pointA.get_Y()) / (pointB.get_X() - pointA.get_X());
	y_intercept = pointA.get_Y() - (slope * pointA.get_X());
}

string Line2D::toString()
{
	ostringstream buffer;
	buffer << "y = ";
	buffer << slope;
	buffer << "x + ";
	buffer << y_intercept;
	return buffer.str();
}

int show_usage()
{
	cout << "Point coordinates format: x y" << endl;
	return 0;
}

bool Line2D::contains(Point2D point)
{
	double epsilon = 1e-9;
	return (abs(y_intercept - (point.get_Y() - (slope * point.get_X()))) < epsilon);
}

int main()
{
	double x, y;
	int i = 0;
	std::string input;
	Point2D a, b, c;
	while (i < 3)
	{
		if (i == 0)
			cout << "Enter first point coordinates: ";
		else if (i == 1)
			cout << "Enter second point coordinates: ";
		else
			cout << "Enter third point coordinates: ";
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
		else if (i == 1)
			b = Point2D(x, y);
		else
			c = Point2D(x, y);
		i++;
	}
	Line2D line = Line2D(a, b);
	cout << (line.contains(c) ? "collinear" : "not collinear") << endl;
	return 0;
}
