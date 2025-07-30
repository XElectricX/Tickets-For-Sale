#pragma once

#include <vector>
#include <string>
#include "code/objects/customers.h"
#include "code/objects/tickets.h"

using std::string;
using std::vector;

//Game state data
struct Game
{
	string player_name;
	string business_name;
	int money;

	//List of owned tickets
	vector<Ticket> ticket_inventory;
	//List of tickets currently for sale
	vector<Ticket_Datum> tickets_for_sale;
	//List of references to customers waiting at the ticket counter
	vector<Customer> customers;

	//Statistics
	int total_customers = 0;
	int total_tickets_sold = 0;
	int total_tickets_bought = 0;
	int total_revenue = 0;
	int total_expenses = 0;
};

//Global variable for the current game's data
extern Game game_data;
