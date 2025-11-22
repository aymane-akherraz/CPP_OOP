#include <iostream>
#include <limits>
#include <stdio.h>
#define MAX_FLIGHTS 10

class FlightBooking {
public:
	FlightBooking(int id, int capacity, int reserved);
	void printStatus();
	void reserveSeats(int number_of_seats);
	void cancelReservations(int number_of_seats);
	int get_id() { return id; }
private:
	int id;
	int capacity;
	int reserved;
};

void FlightBooking::printStatus()
{
	std::cout << "Flight " << this->id << " : " << this->reserved << "/" << this->capacity << " (" << (this->reserved * 100) / this->capacity << "%) seats reserved" << std::endl;
}

bool check_id(int id)
{
	if (id == 0) {
        std::cout << "Cannot perform this operation: flight id can't be 0" << std::endl;
        return false;
    }
	return true;
}

FlightBooking::FlightBooking(int id = 0, int capacity = 0, int reserved = 0)
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

void FlightBooking::reserveSeats(int number_of_seats)
{
	if (number_of_seats <= 0)
		number_of_seats = 0;
	else if (((this->reserved + number_of_seats)) > this->capacity * 1.05) {
		std::cout << "Cannot perform this operation: capacity reached" << std::endl;
		return ;
	}
	this->reserved += number_of_seats;
}

void FlightBooking::cancelReservations(int number_of_seats)
{
	if (number_of_seats <= 0)
        number_of_seats = 0;
	if (number_of_seats > this->reserved) {
		std::cout << "Cannot perform this operation: number of seats provided is greater than the capacity of the flight" << std::endl;
		return;
	}
	this->reserved -= number_of_seats;
}

void create_flight(int id, int capacity, FlightBooking *flights)
{
	if (!check_id(id))
        return;
	bool max_reached = true;
	for (int i = 0; i < MAX_FLIGHTS; i++) {
		if (id == flights[i].get_id()) {
			std::cout << "Flight " << id << " already exist" << std::endl;
			return;
		}
		if (flights[i].get_id() == 0) {
			flights[i] = FlightBooking(id, capacity);
			max_reached = false;
			break;
		}
	}
	if (max_reached)
		std::cout << "Cannot perform this operation: maximum number of flights has been reached, please delete some flights in order to create new ones" << std::endl;
}

void delete_flight(int id, FlightBooking *flights)
{
	if (!check_id(id))
        return;
	bool flight_exist = false;
	 for (int i = 0; i < MAX_FLIGHTS; i++) {
        if (id == flights[i].get_id()) {
			flights[i] = FlightBooking();
			flight_exist = true;
			return ;
		}
	}
	if (!flight_exist)
		std::cout << "Cannot perform this operation: flight " << id << " not found" << std::endl;
}

int main() {
	int seats, id;
	std::string command;
	FlightBooking booking[10];
	while (command != "quit")
	{
		command = "";
		bool flight_exists = false;
		for (int i = 0; i < MAX_FLIGHTS; i++) {
			if (booking[i].get_id() != 0) {
				booking[i].printStatus();
				flight_exists = true;
			}
		}
		if (!flight_exists)
			std::cout << "No flights in the system" << std::endl;
		std::cout << "What would you like to do?: ";
		while (command.empty())
			std::getline(std::cin, command);
		if (sscanf(command.c_str(), "create %d %d", &id, &seats) == 2)
			create_flight(id, seats, booking);
		else if (sscanf(command.c_str(), "delete %d", &id) == 1)
			delete_flight(id, booking);
		else if (sscanf(command.c_str(), "add %d %d", &id, &seats) == 2) {
			if (!check_id(id))
				continue;
			bool flight_found = false;
			for (int i = 0; i < MAX_FLIGHTS; i++) {
		        if (id == booking[i].get_id()) {
					booking[i].reserveSeats(seats);
					flight_found = true;
					break;
				}
			}
			if (!flight_found)
				std::cout << "Cannot perform this operation: flight " << id << " not found" << std::endl;
		}
		else if (sscanf(command.c_str(), "cancel %d %d", &id, &seats) == 2) {
			if (!check_id(id))
                continue;
			bool is_found = false;
            for (int i = 0; i < MAX_FLIGHTS; i++) {
                if (id == booking[i].get_id()) {
                    booking[i].cancelReservations(seats);
                    is_found = true;
                    break;
                }
            }
            if (!is_found)
                std::cout << "Cannot perform this operation: flight " << id << " not found" << std::endl;
		}
		else {
			if (command != "quit")
				std::cout << "Unknown command" << std::endl;
			continue;
		}
	}
	return 0;
}
