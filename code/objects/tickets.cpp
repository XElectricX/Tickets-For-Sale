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
