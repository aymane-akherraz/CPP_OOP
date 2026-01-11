#include <sstream>
#include <iostream>

#define MAX_IPS 3 

using namespace std;

class IPAddress
{
private:
	string ip;
	bool isValid;
public:
	IPAddress() : isValid(false) {};
	IPAddress(string ip);
	void print() const;
	bool get_isValid() const;
	static bool is_valid(const string& ip);
};

void IPAddress::print() const
{
	cout << ip << endl;
}

bool IPAddress::get_isValid() const
{           
    return isValid;
}

IPAddress::IPAddress(string ip) : isValid(false)
{
	if (is_valid(ip))
		isValid = true;
	this->ip = ip;
}

bool IPAddress::is_valid(const string& ip)
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

class Network
{
private:
	size_t idx;
	IPAddress IPs[MAX_IPS];
	static size_t id;
public:
	Network();
	bool add_IP(IPAddress ip);
	void print();
};

size_t Network::id = 0;

Network::Network() : idx(0) 
{
	id++;
}

bool Network::add_IP(IPAddress ip)
{
	if (!ip.get_isValid())
	{
		cout << "Can't add IP: Invalid IP !";
		return false;
	}
	if (idx < MAX_IPS)
	{
		IPs[idx++] = ip;
		return true;
	}
	cout << "Can't add IP: The array is full, Try incrementing MAX_IPS" << endl;
	return false;
}

void Network::print()
{
	cout << "Network " << id << ":" << endl;
	for (int i = 0; i < MAX_IPS; i++)
		IPs[i].print();
}

int main()
{
	string line;
	size_t total_ips = 5;
	string lines[total_ips];
	int i = 0;
	cout << "Enter "<< total_ips << " IP addresses one per line : \n";
	while (i < total_ips && getline(cin, line))
	{
		if (line.empty())
			continue;
		lines[i++] = line;
	}
	Network n1;
	for (int i = 0; i < MAX_IPS; i++)
	{
		if (!n1.add_IP(IPAddress(lines[i])))
			break;
	}
	n1.print();
	Network n2;
    for (int i = (MAX_IPS - 1); i < total_ips; i++)
	{
		if (!n2.add_IP(IPAddress(lines[i])))
			break;
	}
	n2.print();
	return 0;
}
