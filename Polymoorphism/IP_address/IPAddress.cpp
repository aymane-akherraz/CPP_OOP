#include <sstream>
#include <iostream>

using namespace std;

class IPAddress
{
protected:
	string ip;
	static bool check_ip(const string& ip);
public:
	IPAddress(const string& ip);
	IPAddress(const IPAddress& src);
	virtual void print();
};

IPAddress::IPAddress(const string& ip) : ip(ip) {}

IPAddress::IPAddress(const IPAddress& src)
{
	*this = src;
}

bool IPAddress::check_ip(const string& ip)
{
	char dot;
	int n, parts = 0;
	istringstream iss(ip);
	while (iss >> n)
	{
		if (n < 0 || n > 255)
			return false;
		parts++;
		if (parts < 4)
		{
			if (!(iss >> dot) || iss.eof() || dot != '.')
				return false;
		}
	}
	if (!iss.eof())
		iss >> ws;
	if (!iss.eof() || parts != 4)
		return false;
	return true;
}

void IPAddress::print()
{
	cout << ip << endl;
}

class IPAddressChecked : public IPAddress
{
	bool is_valid;
public:
	IPAddressChecked(const string& ip);
	IPAddressChecked(const IPAddressChecked& src);
	void print() override;
};

IPAddressChecked::IPAddressChecked(const string& ip) : IPAddress(ip), is_valid(false) {}

IPAddressChecked::IPAddressChecked(const IPAddressChecked& src) : IPAddress(src) {}

void IPAddressChecked::print()
{
	is_valid = check_ip(ip);
	cout << ip << " - " << (is_valid ? "Correct" : "Not Correct") << endl;
}

int main()
{
	string line;
	string lines[3];
	int i = 0;

	while (getline(cin, line) && i < 3)
	{
		if (line.empty())
			continue;
		lines[i++] = line;
	}
	IPAddress *ips[] = { new IPAddress(lines[0]), new IPAddressChecked(lines[1]), new IPAddressChecked(lines[2]) };
	for (int i = 0; i < 3; i++)
		ips[i]->print();
}
