#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include "code/helpers.h"
#include "code/objects/tickets.h"
#include "code/defines.h"
#include "code/menus/menu_system.h"
#include "code/save_system.h"
#include "code/app/tickets_for_sale_app.h"

using std::ofstream;
using std::string;
using std::to_string;
using json = nlohmann::json;

// Test function to debug ticket lists
void debug_ticket_list(const vector<Ticket> &tickets)
{
	for (const auto &ticket : tickets)
	{
		ticket.test_print();
	}
}

// Copilot: Creates an example GameData object and autosaves it using the autosave function.
void writeExampleAutoSave()
{
	GameData example_data =
		{
			"3",   // game_date
			"60",  // ticket_data (Total Tickets)
			"30",  // TICKET_CLASS_ECONOMY
			"20",  // TICKET_CLASS_BUSINESS
			"10",  // TICKET_CLASS_LUXURY
			"500", // currency_amount
		};

	// Copilot: Call the autosave function to save the example data
	autosaveGameData(example_data);

	print("Example auto-save data written using autosave function.\n");
}

// Initialize test data for development
void initialize_test_data()
{
	std::cout << "=== TICKETS FOR SALE GAME ===" << std::endl;
	std::cout << "Initializing game with sample tickets..." << std::endl;

	// Copilot: Test declaration of a ticket datum and creation of a ticket
	Ticket_Datum ticket_datum(Ticket_Class::TICKET_CLASS_ECONOMY, "New York to Los Angeles", 300, 10);
	vector<Ticket> tickets = ticket_datum.create_ticket(5);

	debug_ticket_list(tickets);

	// Copilot: Test the autosave system with example data
	writeExampleAutoSave();

	std::cout << "\nStarting game interface..." << std::endl;
}

int main(int argc, char *argv[])
{
	try
	{
		// Initialize test data (remove this in production)
		initialize_test_data();

		// Create and run the main application
		TicketsForSaleApp app;
		return app.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "Unknown error occurred!" << std::endl;
		return 1;
	}
}