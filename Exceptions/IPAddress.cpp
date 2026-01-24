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
	static bool isPowerOf2(int rangeValue);
	void print(const string& mask);
};

bool IPAddress::isPowerOf2(int rangeValue)
{
    return !(rangeValue & (rangeValue - 1));
}

IPAddress::IPAddress(const string& ip)
{
	check_ip(ip);
	this->ip = ip;
}

bool IPAddress::check_ip(const string& ip)
{
	char dot;
	int n, parts = 0;
	istringstream iss(ip);
	while (iss >> n)
	{
		if (n < 0 || n > 255)
			throw invalid_argument("invalid IP number " + to_string(n));
		parts++;
		if (parts < 4)
		{
			if (!(iss >> dot) || iss.eof() || dot != '.')
				throw invalid_argument("invalid IP");
		}
	}
	if (!iss.eof())
		iss >> ws;
	if (!iss.eof() || parts != 4)
		throw invalid_argument("invalid IP");
	return true;
}


void IPAddress::print(const string& mask)
{
	int range;
	istringstream iss(mask);
	if (iss >> range)
	{
		if (isPowerOf2(range))
		{
			
			string slice = ip.substr(ip.find_last_of(".") + 1);
			int part = stoi(slice);
			if (part + range > 255)
				throw invalid_argument("invalid IP number - number + mask > 255.");
			string base = ip.substr(0, ip.length() - slice.length());
			for (int i = 1; i <= range; i++)
				cout << base << part + i << endl;
		}
		else
			throw invalid_argument("invalid range");
	}
	else
		throw invalid_argument("invalid range");
}

int main()
{
	string line;
	cout << "Enter IP Address: ";
	if (!getline(cin, line))
		return 0;
	try {
		IPAddress ip(line);
		cout << "Enter Subnet Mask: ";
		if (!getline(cin, line))
	        return 0;
		ip.print(line);
	}
	catch (const invalid_argument& ex) {
        cout << "Exception - " << ex.what() << endl;
	}
}
