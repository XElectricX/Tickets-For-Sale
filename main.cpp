#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "code/helpers.h"
#include "code/objects/tickets.h"	// Include the header file, not the source file
#include "code/defines.h"			// Include defines to use the Ticket_Class enum
#include "code/menus/menu_system.h" // Include the FTXUI menu system
#include "code/objects/tickets.h"	// Include the header file, not the source file
#include "code/menus/main_menu.h"	// Include the menu header file
#include "code/save_system.h"		// Include the save system header file
#include "code/defines.h"			// Include defines to use the Ticket_Class enum

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

int main(int argc, char *argv[])
{
	// Initialize game with some test data
	// Ticket_Datum ticket_datum(Ticket_Class::TICKET_CLASS_ECONOMY, "New York to Los Angeles", 300, 10);
	// vector<Ticket> tickets = ticket_datum.create_ticket(5);

	std::cout << "=== TICKETS FOR SALE GAME ===" << std::endl;
	std::cout << "Initializing game with sample tickets..." << std::endl;
	// debug_ticket_list(tickets); // Debugging function to print ticket details
	std::cout << "\nStarting game interface..." << std::endl;

	// Start the FTXUI menu system
	int current_menu = MENU_START_GAME;
	bool running = true;

	while (running)
	{
		std::cout << "\n[DEBUG] Current menu: " << current_menu << std::endl;

		switch (current_menu)
		{
		case MENU_START_GAME:
			std::cout << "[DEBUG] Showing main menu..." << std::endl;
			current_menu = show_main_menu();
			std::cout << "[DEBUG] Main menu returned: " << current_menu << std::endl;
			break;

		case MENU_TICKET_COUNTER:
			std::cout << "[DEBUG] Showing ticket counter menu..." << std::endl;
			current_menu = show_ticket_counter_menu();
			std::cout << "[DEBUG] Ticket counter returned: " << current_menu << std::endl;
			break;

		case MENU_INVENTORY:
			std::cout << "[DEBUG] Showing inventory menu..." << std::endl;
			current_menu = show_ticket_inventory_menu();
			std::cout << "[DEBUG] Inventory returned: " << current_menu << std::endl;
			break;

		case MENU_PURCHASE:
			std::cout << "[DEBUG] Showing purchase menu..." << std::endl;
			current_menu = show_ticket_purchasing_menu();
			std::cout << "[DEBUG] Purchase returned: " << current_menu << std::endl;
			break;

		case MENU_BARTER:
			std::cout << "[DEBUG] Showing barter menu..." << std::endl;
			current_menu = show_barter_menu();
			std::cout << "[DEBUG] Barter returned: " << current_menu << std::endl;
			break;

		case MENU_STATISTICS:
			std::cout << "[DEBUG] Showing statistics menu..." << std::endl;
			current_menu = show_statistics_menu();
			std::cout << "[DEBUG] Statistics returned: " << current_menu << std::endl;
			break;

		case MENU_LOAD_GAME:
			std::cout << "Loading game... (not implemented yet)" << std::endl;
			current_menu = MENU_TICKET_COUNTER;
			break;

		case MENU_SAVE_GAME:
			std::cout << "Saving game... (not implemented yet)" << std::endl;
			current_menu = MENU_TICKET_COUNTER;
			break;

		case MENU_OPTIONS:
			std::cout << "[DEBUG] Showing options menu..." << std::endl;
			current_menu = show_options_menu();
			std::cout << "[DEBUG] Options returned: " << current_menu << std::endl;
			break;

		case MENU_EXIT:
			std::cout << "[DEBUG] Exit requested" << std::endl;
			std::cout << "Thanks for playing Tickets for Sale!" << std::endl;
			running = false;
			return 0;

		case MENU_BACK:
			std::cout << "[DEBUG] Back requested - returning to main menu" << std::endl;
			current_menu = MENU_START_GAME;
			break;

		default:
			// Handle unexpected menu codes or Ctrl+C exits
			std::cout << "[DEBUG] Unexpected menu code: " << current_menu << std::endl;
			std::cout << "Exiting game..." << std::endl;
			running = false;
			break;
		}

		// Safety check to prevent infinite loops
		if (current_menu < 0 || current_menu > 50)
		{
			std::cout << "[ERROR] Invalid menu code: " << current_menu << std::endl;
			running = false;
		}
	}

	// Copilot: Test declaration of a ticket datum and creation of a ticket
	Ticket_Datum ticket_datum(Ticket_Class::TICKET_CLASS_ECONOMY, "New York to Los Angeles", 300, 10);

	vector<Ticket> tickets = ticket_datum.create_ticket(5);

	debug_ticket_list(tickets);

	// Copilot: Test the autosave system with example data
	writeExampleAutoSave();

	// Create the main menu
	Menu menu = create_or_switch_menu(MAIN_MENU);
	menu.run(); // Run the main menu

	return 0;
}