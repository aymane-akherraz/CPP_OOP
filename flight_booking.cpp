#include <iostream>

class FlightBooking {
public:
	FlightBooking(int id, int capacity, int reserved);
	void printStatus();
	bool reserveSeats(int number_of_seats);
	bool cancelReservations(int number_of_seats);
private:
	int id;
	int capacity;
	int reserved;
};

void FlightBooking::printStatus()
{
	std::cout << "Flight " << id << " : " << reserved << "/" << capacity << " (" << (reserved * 100) / capacity << "%) seats reserved" << std::endl;
}

FlightBooking::FlightBooking(int id, int capacity, int reserved)
{
	this->id = id;
	if (capacity <= 0)
		this->capacity = 1;
	else
		this->capacity = capacity;
	if (reserved <= 0)
		reserved = 0;
	if (((reserved * 100) / this->capacity) > 105)
		this->reserved = (105 * this->capacity) / 100;
	else
		this->reserved = reserved;
}

bool FlightBooking::reserveSeats(int number_of_seats)
{
	if (number_of_seats <= 0)
		number_of_seats = 0;
	else if ((((this->reserved + number_of_seats) * 100) / this->capacity) > 105)
		return false;
	this->reserved += number_of_seats;
	return true;
}

bool FlightBooking::cancelReservations(int number_of_seats)
{
	if (number_of_seats <= 0)
        number_of_seats = 0;
	if (number_of_seats > this->reserved)
		return false;
	this->reserved -= number_of_seats;
	return true;
}

int main() {
	int reserved = 0,
	  capacity = 0;
	std::cout << "Provide flight capacity: ";
	std::cin >> capacity;

	std::cout << "Provide number of reserved seats: ";
	std::cin >> reserved;

	FlightBooking booking(1, capacity, reserved);
	std::string command = "";
	while (command != "quit")
	{
		booking.printStatus();
		std::cout << "What would you like to do?: ";
		std::getline(std::cin, command);
		size_t pos = command.find(' ');
		if (command != "quit" && pos != std::string::npos)
		{
			std::string cmd = command.substr(0, pos);
			if (cmd != "add" && cmd != "cancel")
				std::cout << "Invalid command" << std::endl;
			else
			{
				std::string num_of_seats = command.substr(pos + 1);
				try {
        			int number = std::stoi(command);
					if (cmd == "add")
						booking.reserveSeats(number);
					else
						booking.cancelReservations(number);
				}
				catch (const std::invalid_argument& e) {
					std::cerr << "Error: The input provided is not a valid number." << std::endl;
					std::cerr << "Exception details: " << e.what() << std::endl;
				}
			}
		}
		else
			std::cout << "Invalid command" << std::endl;
	}
	return 0;
}
