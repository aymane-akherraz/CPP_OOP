#include <iostream>
#include <sstream>

#define MAX_ROWS 2
#define MAX_COLS 2

using namespace std;

class Matrix
{
	size_t i;
	size_t j;
	int m[MAX_ROWS][MAX_COLS];
public:
	Matrix();
	void operator<<(int val);
	friend ostream& operator<<(ostream& os, const Matrix& obj);
};

Matrix::Matrix() : i(0), j(0)
{
	for (size_t i = 0; i < MAX_ROWS; i++)
	{
		for (size_t j = 0; j < MAX_COLS; j++)
			m[i][j] = 0;
	}
}

void Matrix::operator<<(int val)
{
	m[i][j] = val;
	((j + 1) % MAX_COLS) ? j++ : j = 0;
	if (j == 0)
		((i + 1) % MAX_ROWS) ? i++ : i = 0;
}

ostream& operator<<(ostream& os, const Matrix& obj)
{
	for (size_t i = 0; i < MAX_ROWS; i++)
	{
		for (size_t j = 0; j < MAX_COLS; j++)
		{
			os << obj.m[i][j];
			if (j < (MAX_COLS - 1))
				os << " ";
		}
		os << endl;
	}
	return os;
}

int main()
{
	Matrix m;
	size_t size = MAX_ROWS * MAX_COLS;
	cout << "Enter the " << size << " values of the matrix " << MAX_ROWS << "x" << MAX_COLS << " one number per line: \n";
	for (size_t i = 0; i < size; i++)
	{
		string line;
		if (getline(cin, line))
		{
			istringstream iss(line);
			int val;
			if (iss >> val)
				m << val;
		}
	}
	cout << m;
}
