#include <iostream>
#include <sstream>

#define TOTAL_DISKS 3

using namespace std;

class Disk
{
private:
	size_t size;
public:
	size_t get_size();
	void set_size(size_t new_size);
};

void Disk::set_size(size_t new_size)
{
	size = new_size;
}

size_t Disk::get_size()
{
	return size;
}

class Tower
{
private:
	Disk disks[TOTAL_DISKS];
	static int id;
	int tower_number;
	int num_of_disks;
public:
	Tower();
	static void move_disk(Tower& src, Tower& dest);
	static void print(Tower *t);
};

int Tower::id = 1;

Tower::Tower() : tower_number(id++), num_of_disks(0)
{
	if (tower_number == 1)
	{
		for (int i = 0; i < TOTAL_DISKS; i++)
			disks[i].set_size(TOTAL_DISKS - i);
		num_of_disks = TOTAL_DISKS;
	}
}

void Tower::move_disk(Tower& src, Tower& dest)
{
	if (src.num_of_disks)
	{
		if (src.disks[src.num_of_disks - 1].get_size() > dest.disks[dest.num_of_disks - 1].get_size())
			throw logic_error("Can't move disk: the disk is bigger than the one in the target tower");
		src.num_of_disks--;
		dest.disks[dest.num_of_disks].set_size(src.disks[src.num_of_disks].get_size());
		dest.num_of_disks++;
		src.disks[src.num_of_disks].set_size(0);
	}
	else
		throw logic_error("Can't move disk: Source tower is empty!");
}

void Tower::print(Tower *t)
{
	for (int i = 0; i < TOTAL_DISKS; i++)
	{
		cout << "tower_" << t[i].tower_number << ": ";
		if (t[i].num_of_disks)
		{
			for (int j = 0; j < t[i].num_of_disks; j++)
			{
				cout << t[i].disks[j].get_size();
				if (j < t[i].num_of_disks - 1)
					cout << " ";
			}
			cout << endl;
		}
		else
			cout << "empty" << endl;
	}
}

int main()
{
	Tower t[3] = { Tower(), Tower(), Tower() };
	cout << "Available commands:\n"
	     << "0 exit\n"
		 << "12 means move disk from tower 1 to tower 2, keep in mind that you have only 3 Towers (1, 3)\n"
		 << "Enter a command:" << endl;
	int cmd;
	string line;
	Tower::print(t);
	while (getline(cin, line))
	{
		istringstream iss(line);
		try {
			if (iss >> cmd)
			{
				if (cmd == 0)
					break;
				int i = 0;
				int div = cmd / 10;
				while (i < 2 && div)
				{
					div /= 10;
					i++;
				}
				int src_tower = cmd / 10;
				int dest_tower = cmd % 10;
				if (i != 1 || src_tower < 1 || src_tower > 3 || dest_tower < 1 || dest_tower > 3)
					throw logic_error("Invalid command: please enter 2 digits between 1 and 3");
				if (src_tower != dest_tower)
					Tower::move_disk(t[src_tower - 1], t[dest_tower - 1]);
				Tower::print(t);
			}
			else
				throw logic_error("Invalid command: please enter 2 digits between 1 and 3");
		}
		catch (const logic_error& ex){
			cout << ex.what() << endl;
		}
	}
}
