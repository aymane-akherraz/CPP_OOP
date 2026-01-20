#include <iostream>
#include <sstream>
#include <stdexcept>

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
	Matrix& operator-(Matrix& b);
	Matrix& operator+(Matrix& b);
	Matrix* operator*(Matrix& b);
	Matrix(size_t rows, size_t cols);
	void add_value(int value) throw(runtime_error, ios_base);
	void subtract_value(int value) throw(runtime_error, ios_base);
	void multiply_value(int value) throw(runtime_error, ios_base);
	void init_matrix(Matrix& matrix) throw(runtime_error, ios_base);
	void add(Matrix& b) throw(runtime_error, ios_base, invalid_argument);
	void subtract(Matrix& b) throw(runtime_error, ios_base, invalid_argument);
	void multiply(Matrix& b) throw(runtime_error, ios_base, invalid_argument);
	friend ostream& operator<<(ostream& os, const Matrix& obj);
};

char Matrix::symbol = 'A';

Matrix::Matrix()
    : m(NULL), name(symbol++), rows(0), cols(0) {}

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

void Matrix::init_matrix(Matrix& matrix) throw(runtime_error, ios_base)
{
	string line;
	cout << "Enter the number of rows for Matrix " << matrix.name << ": ";
	if (!getline(cin, line))
    	throw ios_base::failure("");
	int rows;
	istringstream iss(line);
	if (iss >> rows && rows > 0)
	{
		cout << "Enter the number of columns for Matrix "<< matrix.name << ": ";
		if (!getline(cin, line))		
			throw ios_base::failure("");
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
					if (!getline(cin, line))
						throw ios_base::failure("");
					int value;
					istringstream iss(line);
					if (iss >> value)
						matrix.m[i][j] = value;
					else
						throw runtime_error("Invalid number!");
				}
			}
		}
		else
			throw runtime_error("Invalid number!");
	}
	else
		throw runtime_error("Invalid number!");
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

void Matrix::add(Matrix& b) throw(runtime_error, ios_base, invalid_argument)
{
	init_matrix(*this);
	init_matrix(b);
	cout << *this << b;
	if (this->rows != b.rows || this->cols != b.cols)
		throw invalid_argument(
            "Matrix sizes do not match for addition"
        );
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

void Matrix::subtract(Matrix& b) throw(runtime_error, ios_base, invalid_argument)
{
	init_matrix(*this);
	init_matrix(b);
	cout << *this << b;
	if (this->rows != b.rows || this->cols != b.cols)
		throw invalid_argument(
            "Matrix sizes do not match for subtraction"
        );
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

void Matrix::multiply(Matrix& b) throw(runtime_error, ios_base, invalid_argument)
{
	init_matrix(*this);
	init_matrix(b);
	cout << *this << b;
	if (this->cols != b.rows)
		throw std::invalid_argument(
            "Matrix sizes do not match for multiplying"
        );
	else
	{
		cout << "After multiplying:\n";
		Matrix *res = *this * b;
		Matrix& result = *res;
		cout << result;
		delete res;
	}
}

int get_value() throw(runtime_error, ios_base)
{
	string line;
	cout << "Enter the value: ";
	if (!getline(cin, line))
		throw ios_base::failure("");
	int value;
	istringstream iss(line);
	try {
		if (iss >> value)
			return value;
		throw runtime_error("Invalid number!");
	}
	catch (const runtime_error& e) {
		throw e;
	}
}

void Matrix::add_value(int value) throw(runtime_error, ios_base)
{
	init_matrix(*this);
	cout << *this;
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
			m[i][j] += value;
	}
	cout << "After adding " << value << " :\n";
	cout << *this;
}

void Matrix::subtract_value(int value) throw(runtime_error, ios_base)
{
	init_matrix(*this);
	cout << *this;
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
			m[i][j] -= value;
	}
	cout << "After subtracting " << value << " :\n";
	cout << *this;

}

void Matrix::multiply_value(int value) throw(runtime_error, ios_base)
{
	init_matrix(*this);
	cout << *this;
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
			m[i][j] *= value;
	}
	cout << "After multiplying " << value << " :\n";
	cout << *this;
}

int main()
{
	string line;
	cout << "Enter the number of the operation you want to perform:\n";
	cout << "0- Exit\n";
	cout << "1- Add a value to a matrix\n";
	cout << "2- subtract a value form a matrix\n";
	cout << "3- multiply a matrix by a value\n";
	cout << "4- Add a matrix to another matrix\n";
    cout << "5- subtract a matrix form another matrix\n";
    cout << "6- multiply a matrix by another matrix\n";
	if (getline(cin, line))
	{
		int choice;
		istringstream iss(line);
		if (iss >> choice)
		{
			Matrix A;
			Matrix B;
			try {
				switch (choice)
				{
						case 0:
							return 0;
						case 1:
							A.add_value(get_value());
							break;
						case 2:
							A.subtract_value(get_value());
							break;
						case 3:
							A.multiply_value(get_value());
							break;
						case 4: 
							A.add(B);
							break;
						case 5:
							A.subtract(B);
							break;
						case 6:
							A.multiply(B);
							break;
						default:
						cout << "Invalid command\n";
				}
			}
			catch (const ios_base::failure& e) {
			    cout << "\nInput ended";
			}
			catch (const runtime_error& e) {
				cerr << "Bad input: " << e.what() << endl;
			}
			catch (const invalid_argument& e) {
				cerr << e.what() << endl;
			}
		}
	}
}
