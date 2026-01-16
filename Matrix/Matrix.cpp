#include <iostream>
#include <sstream>

using namespace std;

class Matrix
{
	int	**m;
	char name;
	size_t rows;
	size_t cols;
	static char symbol;
public:
	Matrix();
	~Matrix();
	void add(Matrix& b);
	void subtract(Matrix& b);
	void multiply(Matrix& b);
	Matrix& operator-(Matrix& b);
	Matrix& operator+(Matrix& b);
	Matrix* operator*(Matrix& b);
	bool init_matrix(Matrix& matrix);
	Matrix(size_t rows, size_t cols);
	friend ostream& operator<<(ostream& os, const Matrix& obj);
};

char Matrix::symbol = 'A';

Matrix::Matrix()
    : m(nullptr), name(symbol++), rows(0), cols(0) {}

Matrix::~Matrix()
{
	for (size_t i = 0; i < rows; i++)
    	delete[] m[i];
	delete[] m;
}

Matrix::Matrix(size_t rows, size_t cols) : name(symbol++), rows(rows), cols(cols)
{
	m = new int *[rows];
	for (size_t i = 0; i < rows; i++)
	{
		m[i] = new int[cols];
		for (size_t j = 0; j < cols; j++)
			m[i][j] = 0;
	}
}

bool Matrix::init_matrix(Matrix& matrix)
{
	string line;
	cout << "Enter the number of rows for Matrix " << matrix.name << ": ";
	if (getline(cin, line))
    {
		int rows;
		istringstream iss(line);
		if (iss >> rows && rows > 0)
		{
			cout << "Enter the number of columns for Matrix "<< matrix.name << ": ";
			if (getline(cin, line))
			{
				int cols;
		        istringstream iss(line);
				if (iss >> cols && cols > 0)
				{
					matrix.rows = rows;
					matrix.cols = cols;
					matrix.m = new int *[rows];
					for (int i = 0; i < rows; i++)
						matrix.m[i] = new int[cols];
					cout << "Enter the values for Matrix " << matrix.name << ":\n";
					for (int i = 0; i < rows; i++)
					{
						for (int j = 0; j < cols; j++)
						{
							cout << "Enter value at position [" << i << "][" << j << "]: ";
							if (getline(cin, line))
							{
								int value;
								istringstream iss(line);
								if (iss >> value)
									matrix.m[i][j] = value;
							}
							else
								return false;
						}
					}
				}
				else
				{
		            cout << "Invalid number: please enter a positive number\n";
					return false;
				}
			}
			else
				return false;
		}
		else
		{
			cout << "Invalid number: please enter a positive number\n";
			return false;
		}
	}
	else
		return false;
	return true;
}

ostream& operator<<(ostream& os, const Matrix& obj)
{
	os << "Matrix " << obj.name << ":\n";
	for (size_t i = 0; i < obj.rows; i++)
	{
		for (size_t j = 0; j < obj.cols; j++)
		{
			os << obj.m[i][j];
			if (j < (obj.cols - 1))
				os << " ";
		}
		os << endl;
	}
	return os;
}

Matrix& Matrix::operator+(Matrix& b)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
			m[i][j] += b.m[i][j];
	}
	return *this;
}

void Matrix::add(Matrix& b)
{
	if (!init_matrix(*this) || !init_matrix(b))
		return ;
	cout << *this << b;
	if (this->rows != b.rows || this->cols != b.cols)
		cout << "Matrix sizes do not match for addition!\n";
	else
	{
		cout << "After addition:\n";
		cout << (*this + b);
	}
}

Matrix& Matrix::operator-(Matrix& b)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
			m[i][j] -= b.m[i][j];
	}
	return *this;
}

void Matrix::subtract(Matrix& b)
{
	if (!init_matrix(*this) || !init_matrix(b))
		return ;
	cout << *this << b;
	if (this->rows != b.rows || this->cols != b.cols)
		cout << "Matrix sizes do not match for subtraction!\n";
	else
	{
		cout << "After subtraction:\n";
		cout << *this - b;
	}
}

Matrix* Matrix::operator*(Matrix& b)
{
	Matrix *result = new Matrix(rows, b.cols);
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < b.cols; j++)
		{
			for (size_t k = 0; k < cols; k++)
				result->m[i][j] += m[i][k] * b.m[k][j];
		}
	}
	return result;
}

void Matrix::multiply(Matrix& b)
{
	if (!init_matrix(*this) || !init_matrix(b))
		return ;
	cout << *this << b;
	if (this->cols != b.rows)
		cout << "Matrix sizes do not match for multiplying!\n";
	else
	{
		cout << "After multiplying:\n";
		Matrix *res = *this * b;
		Matrix& result = *res;
		cout << result;
		delete res;
	}
}

int main()
{
	string line;
	cout << "Enter the operation you want to perform (add, subtract, multiply): ";
	if (getline(cin, line))
	{
		istringstream iss(line);
		if (iss >> line)
		{
			Matrix A;
			Matrix B;
			if (line == "add")
				A.add(B);
			else if (line == "subtract")
				A.subtract(B);
			else if (line == "multiply")
				A.multiply(B);
			else
				cout << "Invalid command\n";
		}
	}
}
