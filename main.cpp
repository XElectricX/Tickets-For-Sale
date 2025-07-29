#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "code/helpers.h"
#include "code/objects/tickets.h" // Include the header file, not the source file
#include "code/menus/main_menu.h" // Include the menu header file
#include "code/save_system.h" // Include the save system header file
#include "code/defines.h"         // Include defines to use the Ticket_Class enum

using std::string;
using std::to_string;
using std::ofstream;
using json = nlohmann::json;

//Test function to debug ticket lists
void debug_ticket_list(const vector<Ticket>& tickets)
{
	for(const auto& ticket : tickets)
	{
		ticket.test_print();
	}
}

// Copilot: Creates an example GameData object and autosaves it using the autosave function.
void writeExampleAutoSave()
{
	GameData example_data =
	{
		"3", // game_date
		"60", // ticket_data (Total Tickets)
		"30", // TICKET_CLASS_ECONOMY
		"20", // TICKET_CLASS_BUSINESS
		"10", // TICKET_CLASS_LUXURY
		"500", // currency_amount
	};

	// Copilot: Call the autosave function to save the example data
	autosaveGameData(example_data);

	print("Example auto-save data written using autosave function.\n");
}


int main(int argc, char* argv[])
{
	// Copilot: Test declaration of a ticket datum and creation of a ticket
	Ticket_Datum ticket_datum(Ticket_Class::TICKET_CLASS_ECONOMY, "New York to Los Angeles", 300, 10);

	vector<Ticket> tickets = ticket_datum.create_ticket(5);

	debug_ticket_list(tickets);

	// Copilot: Test the autosave system with example data
	writeExampleAutoSave();

	//Create the main menu
	Menu menu = create_or_switch_menu(MAIN_MENU);
	menu.run(); // Run the main menu

	return 0;
}