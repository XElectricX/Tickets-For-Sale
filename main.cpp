#include <iostream>
#include <string>
#include <vector>
#include "code/helpers.h"
#include "code/objects/tickets.h" // Include the header file, not the source file
#include "code/defines.h"         // Include defines to use the Ticket_Class enum
using std::string;
using std::to_string;

//Test function to debug ticket lists
void debug_ticket_list(const vector<Ticket>& tickets)
{
	for(const auto& ticket : tickets)
	{
		ticket.test_print();
	}
}

int main(int argc, char* argv[])
{
	//Test declaration of a ticket datum and creation of a ticket
	Ticket_Datum ticket_datum(Ticket_Class::TICKET_CLASS_ECONOMY, "New York to Los Angeles", 300, 10);
	vector<Ticket> tickets = ticket_datum.create_ticket(5);
	debug_ticket_list(tickets);
	return 0;
}