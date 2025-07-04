#pragma once

#include <string>
#include <vector>
#include "../defines.h"
using std::string;
using std::vector;

//The actual ticket entity
class Ticket
{
public:
	Ticket_Class ticket_class;
	int price_paid;
	string route;

	//Debug function to display ticket data
	void test_print() const;

	Ticket(Ticket_Class ticket_class, int price_paid, string route);
};

/*** Ticket_Datum has to go after Ticket because it uses Ticket, otherwise the program explodes! ***/

//Hold the ticket data for the ticket system; not the actual tickets themselves
class Ticket_Datum
{
public:
	Ticket_Class ticket_class;
	string route;
	int price;
	int amount_available;

	vector<Ticket> create_ticket(int amount_to_create);

	//Constructor
	Ticket_Datum(Ticket_Class ticket_class, string route, int price, int amount_available);
};
