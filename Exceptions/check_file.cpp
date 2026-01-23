#include <iostream>
#include <fstream>
#include <sstream>
#include <cerrno>

#define ROWS 2
#define COLS 2

using namespace std;

class FileException : public exception {
public:
    explicit FileException(const string& message) : message_(message) {}
    const char* what() const noexcept override {
        return message_.c_str();
    }
private:
    string message_;
};

class Matrix
{
	int m[ROWS][COLS];
public:
	void load_from_file(const string& path_to_file);
	void save_to_file(const string& path_to_file);
};

void Matrix::load_from_file(const string& path_to_file)
{
	 ifstream file(path_to_file);

    if (!file.is_open())
    {
		if (errno == ENOENT)
			throw FileException("File not found at: " + path_to_file);
		if (errno == EACCES)
			throw FileException("No rights to read from file: " + path_to_file);
    }
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				if (!(file >> m[i][j]))
					throw FileException("Error reading from file: " + path_to_file);
			}
		}
	}
}

void Matrix::save_to_file(const string& path_to_file)
{
	ofstream outf(path_to_file);
	if (!outf.is_open())
    {
		if (errno == EACCES)
            throw FileException("No rights to write to file: " + path_to_file);
	}
	for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
			outf << m[i][j] << endl;
	}
}

int main()
{
	Matrix m;
	try {
		m.load_from_file("matrix.txt");
		m.save_to_file("file.txt");
	}
	catch (const FileException& e) {
		cout << e.what() << endl;
	}
}
