#include <iostream>
#include <array>
#include <sstream>

#define MAX_FLIGHTS 10
#define MAX_BOOKING_PERCENT 1.05

class FlightBooking {
public:
    FlightBooking(int id = 0, int capacity = 1, int reserved = 0)
        : id(id), capacity(capacity > 0 ? capacity : 1)
    {
        this->reserved = std::min(reserved, static_cast<int>(this->capacity * MAX_BOOKING_PERCENT));
    }

    void printStatus() const {
        std::cout << "Flight " << id << " : " << reserved << "/" << capacity
                  << " (" << (reserved * 100) / capacity << "%) seats reserved\n";
    }

    void reserveSeats(int number_of_seats) {
        if (number_of_seats <= 0) return;

        if (reserved + number_of_seats > static_cast<int>(capacity * MAX_BOOKING_PERCENT)) {
            std::cout << "Cannot perform this operation: capacity reached\n";
            return;
        }
        reserved += number_of_seats;
    }

    void cancelReservations(int number_of_seats) {
        if (number_of_seats <= 0) return;

        if (number_of_seats > reserved) {
            std::cout << "Cannot perform this operation: number of seats provided is greater than reserved seats\n";
            return;
        }
        reserved -= number_of_seats;
    }

    int getId() const { return id; }

    static void createFlight(int id, int capacity);
    static void deleteFlight(int id);
    static FlightBooking* findFlight(int id);
    static void printAllFlights();

private:
    int id;
    int capacity;
    int reserved;

    static std::array<FlightBooking, MAX_FLIGHTS> flights;
    static bool checkId(int id) {
        if (id <= 0) {
			std::cout << "Cannot perform this operation: flight id should be greater than 0\n";
			return false;
		}
        return true;
    }
};

std::array<FlightBooking, MAX_FLIGHTS> FlightBooking::flights;

FlightBooking* FlightBooking::findFlight(int id) {
    for (auto &f : flights)
        if (f.getId() == id) return &f;
    return nullptr;
}

void FlightBooking::createFlight(int id, int capacity) {
    if (!checkId(id)) return;

    if (findFlight(id)) {
        std::cout << "Flight " << id << " already exists\n";
        return;
    }

    for (auto &f : flights) {
        if (f.getId() == 0) {
            f = FlightBooking(id, capacity);
            return;
        }
    }

    std::cout << "Cannot perform this operation: maximum number of flights reached\n";
}

void FlightBooking::deleteFlight(int id) {
    if (!checkId(id)) return;

    FlightBooking* f = findFlight(id);
    if (!f) {
        std::cout << "Cannot perform this operation: flight " << id << " not found\n";
        return;
    }
    *f = FlightBooking(); // reset to default
}

void FlightBooking::printAllFlights() {
    bool any = false;
	std::cout << std::endl;
    for (const auto &f : flights) {
        if (f.getId() != 0) {
			if (!any)
				std::cout << "Flights in the system:\n";
            f.printStatus();
            any = true;
        }
    }
    if (!any) std::cout << "No flights in the system\n";
}

static void printFlightMenu() {
    std::cout << "\n=== Flight Booking System ===\n";
    std::cout << "Available commands:\n";
    std::cout << "  create [id] [cap]   - Create a new flight with capacity cap\n";
    std::cout << "  delete [id]         - Delete a flight\n";
    std::cout << "  add [id] [n]        - Add n reservations to the flight\n";
    std::cout << "  cancel [id] [n]     - Cancel n reservations from the flight\n";
    std::cout << "  quit                - Exit the program\n";
    std::cout << "-----------------------------------------\n";
}

int main() {
    std::string command;

    while (true) {
        FlightBooking::printAllFlights();
		printFlightMenu();
        std::cout << "What would you like to do?: ";
        std::getline(std::cin, command);
        if (command.empty()) continue;
        if (command == "quit") break;

        std::istringstream iss(command);
        std::string cmd;
        int id, seats;
        iss >> cmd;

        if (cmd == "create" && iss >> id >> seats) {
            FlightBooking::createFlight(id, seats);
        }
        else if (cmd == "delete" && iss >> id) {
            FlightBooking::deleteFlight(id);
        }
        else if (cmd == "add" && iss >> id >> seats) {
            FlightBooking* f = FlightBooking::findFlight(id);
            if (!f) {
                std::cout << "Cannot perform this operation: flight " << id << " not found\n";
            } else {
                f->reserveSeats(seats);
            }
        }
        else if (cmd == "cancel" && iss >> id >> seats) {
            FlightBooking* f = FlightBooking::findFlight(id);
            if (!f) {
                std::cout << "Cannot perform this operation: flight " << id << " not found\n";
            } else {
                f->cancelReservations(seats);
            }
        }
        else
            std::cout << "Unknown command\n";
    }

    return 0;
}
