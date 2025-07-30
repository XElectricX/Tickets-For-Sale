#include <vector>
#include <utility>
#include "tickets.h"
#include "../helpers.h"
#include "../defines.h"
using std::string;
using std::move;
using std::vector;

Ticket_Datum::Ticket_Datum(Ticket_Class ticket_class, string route, int price, int amount_available)
	//Initializer list
	: ticket_class(ticket_class), route(move(route)), price(price), amount_available(amount_available)
{}

vector<Ticket> Ticket_Datum::create_ticket(int amount_to_create)
{
	vector<Ticket> tickets;
	for(int i = 0; i < amount_to_create; ++i)
	{
		if(amount_available <= 0)
		{
			//If no tickets are available, break the loop
			break;
		}
		//If no tickets are available, return an empty ticket
		tickets.push_back(Ticket(ticket_class, price, route));
		--amount_available;
	}
	return tickets;
}


Ticket::Ticket(Ticket_Class ticket_class, int price_paid, string route)
	//Initializer list
	: ticket_class(ticket_class), price_paid(price_paid), route(move(route))
{}

void Ticket::test_print() const
{
	print("Ticket: " + route + "\n"
		  "Class: " + std::to_string(static_cast<int>(ticket_class)) + "\n"
		  "Price Paid: " + std::to_string(price_paid));
}

// Helper: Generate a random ticket inventory
std::vector<Ticket> random_ticket_inventory(std::mt19937& rng) {
	std::vector<Ticket> tickets;
	std::vector<std::pair<Ticket_Class, std::string>> routes = {
		{Ticket_Class::TICKET_CLASS_ECONOMY, "New York to Los Angeles"},
		{Ticket_Class::TICKET_CLASS_BUSINESS, "Chicago to Miami"},
		{Ticket_Class::TICKET_CLASS_LUXURY, "San Francisco to Paris"},
		{Ticket_Class::TICKET_CLASS_ECONOMY, "Dallas to Seattle"},
		{Ticket_Class::TICKET_CLASS_BUSINESS, "Boston to London"}
	};
	int num_tickets = 3 + (rng() % 4); // 3-6 tickets
	for (int i = 0; i < num_tickets; ++i) {
		auto& r = routes[rng() % routes.size()];
		int price = 50 + (rng() % 200);
		tickets.emplace_back(r.first, price, r.second);
	}
	return tickets;
}
