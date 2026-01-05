#include <iostream>
#include <sstream>
#define MAX_MEMBERS 10

class GymMembership {
	int id;
	std::string name;
	int subscription_months;
	static GymMembership members[MAX_MEMBERS];
public:
	GymMembership(int id, std::string name, int subscription_months);
	static void print_members();
	static void delete_member(int id);
	static GymMembership* find_member(int id);
	static void create_member(int id, std::string name);
	void cancel_subscription() { this->subscription_months = 0; }
	void extend_subscription(int months) { this->subscription_months += months; }
};

GymMembership::GymMembership(int id = 0, std::string name = "", int subscription_months = 0)
{
	this->id = id;
	this->name = name;
	this->subscription_months = subscription_months;
}

static bool check_id(int id) {
	if (id <= 0) {
		std::cout << "Flight id should be greater than 0\n";
		return false;
	}
	return true;
}

static void trim(std::string& s) {
    const std::string whitespace = " \t\n\r\f\v";
    size_t first = s.find_first_not_of(whitespace);
    if (first == std::string::npos) {
        s.clear();
        return;
    }
    size_t last = s.find_last_not_of(whitespace);
    s.assign(s.substr(first, (last - first + 1)));
}

void GymMembership::print_members()
{
	bool any = false;
	std::cout << std::endl;
	for (auto member : members) {
		if (member.id != 0) {
			if (!any)
				std::cout << "Members in the system: " << std::endl;
			std::cout << "Memeber " << member.id << " : " << member.name <<
			", subscription valid for " << member.subscription_months << " months" << std::endl;
			any = true;
		}
	}
	if (!any)
		std::cout << "No members in the system" << std::endl;
}

GymMembership GymMembership::members[MAX_MEMBERS];

GymMembership* GymMembership::find_member(int id)
{
	for (auto &member : members) {
		if (member.id == id)
			return &member;
	}
	return nullptr;
}

void GymMembership::create_member(int id, std::string name)
{
	if (!check_id(id))
		return;
	if (find_member(id)) {
		std::cout << "User id already exist" << std::endl;
		return;
	}
	for (auto &member : members) {
		if (member.id == 0) {
			member = GymMembership(id, name);
			return;
		}
	}
	std::cout << "Maximum members reached, please delete some members in order to create new ones" << std::endl;
}

void GymMembership::delete_member(int id)
{
	if (!check_id(id))
        return;
	GymMembership* member = find_member(id);
    if (find_member(id))
		*member = GymMembership();
	else
        std::cout << "User " << id <<" not found" << std::endl;
}

static void printMenu() {
    std::cout << "\n=== Gym Membership Manager ===\n";
    std::cout << "Available commands:\n";
    std::cout << "  create [id] [name]   - Create a new member\n";
    std::cout << "  delete [id]          - Remove a member\n";
    std::cout << "  extend [id] [n]      - Extend membership by n months\n";
    std::cout << "  cancel [id]          - Set membership to 0 months\n";
    std::cout << "  quit                 - Exit the program\n";
    std::cout << "-----------------------------------------\n";
}

int main()
{
	int id, months;
	std::string line, name, cmd;
	GymMembership* member;
	while (line != "quit") {
		GymMembership::print_members();
		printMenu();	
		std::cout << "What would you like to do?: ";
		std::getline(std::cin, line);
		if (line.empty())
			continue;
		std::istringstream iss(line);
		iss >> cmd;
		if (cmd == "create" && iss >> id) {
			std::getline(iss, name);
			if (name.empty())
				std::cout << "Name is missing" << std::endl;
			else {
				trim(name);
				GymMembership::create_member(id, name);
			}
		}
		else if (cmd == "delete" && iss >> id) {
            GymMembership::delete_member(id);
        }
		else if (cmd == "cancel" && iss >> id) {
			member = GymMembership::find_member(id);
			if (member)
				member->cancel_subscription();
			else
				std::cout << "User " << id <<" not found" << std::endl;
		}
		else if (cmd == "extend" && iss >> id >> months) {
			if (months > 0) {
				member = GymMembership::find_member(id);
	            if (member)
					member->extend_subscription(months);
				else
	                std::cout << "User " << id <<" not found" << std::endl;
			}
			else
				std::cout << "Number of months should be greater than 0" << std::endl;
		}
		else if (cmd != "quit")
			std::cout << "Unknown command" << std::endl;
	}
}
