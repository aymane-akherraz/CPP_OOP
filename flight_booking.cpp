#include <iostream>
#include <limits>
#include <stdio.h>
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
	else if (((this->reserved + number_of_seats)) > this->capacity * 1.05)
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
	int reserved = 0, capacity = 0, seats = 0;
	std::string command;
	std::cout << "Provide flight capacity: ";
	std::cin >> capacity;

	std::cout << "Provide number of reserved seats: ";
	std::cin >> reserved;

	FlightBooking booking(1, capacity, reserved);
	bool res = true;
	while (command != "quit")
	{
		command = "";
		if (res)
			booking.printStatus();
		std::cout << "What would you like to do?: ";
		while (command.empty())
			std::getline(std::cin, command);
		if (sscanf(command.c_str(), "add %d", &seats))
			res = booking.reserveSeats(seats);
		else if (sscanf(command.c_str(), "cancel %d", &seats))
			res = booking.cancelReservations(seats);
		else {
			if (command != "quit")
				std::cout << "Unknown command" << std::endl;
			continue;
		}
		if (!res)
			std::cout << "Cannot perform this operation" << std::endl;
	}
	return 0;
}
