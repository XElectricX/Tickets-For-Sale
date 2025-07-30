#pragma once

#include <string>
#include <vector>
#include <random>
#include "../defines.h"
using std::string;
using std::vector;

// The actual ticket entity
class Ticket
{
public:
	Ticket_Class ticket_class;
	int price_paid;
	string route;

	// Debug function to display ticket data
	void test_print() const;

	// Default constructor for JSON deserialization
	Ticket() : ticket_class(Ticket_Class::TICKET_CLASS_ECONOMY), price_paid(0), route("") {}

	Ticket(Ticket_Class ticket_class, int price_paid, string route);
};

// Helper: Generate a random ticket inventory (definition in tickets.cpp)
std::vector<Ticket> random_ticket_inventory(std::mt19937 &rng);

/*** Ticket_Datum has to go after Ticket because it uses Ticket, otherwise the program explodes! ***/

// Hold the ticket data for the ticket system; not the actual tickets themselves
class Ticket_Datum
{
public:
	Ticket_Class ticket_class;
	string route;
	int price;
	int amount_available;

	vector<Ticket> create_ticket(int amount_to_create);

	// Default constructor for JSON deserialization
	Ticket_Datum() : route(""), price(0), amount_available(0), ticket_class(Ticket_Class::TICKET_CLASS_ECONOMY) {}

	Ticket_Datum(Ticket_Class ticket_class, string route, int price, int amount_available);
};

// Helper: Generate random tickets for sale from suppliers (definition in tickets.cpp)
std::vector<Ticket_Datum> random_tickets_for_sale(std::mt19937 &rng);
