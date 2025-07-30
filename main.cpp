#include <random>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
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
#include "code/game.h"
#include "code/objects/customers.h"

using std::ofstream;
using std::string;
using std::to_string;
using json = nlohmann::json;

Game game_data;

// Helper: Fill game_data with random customers and tickets
void fill_game_with_random_data(Game& g, const NameLists& names, std::mt19937& rng) {
	g.customers.clear();
	for (int i = 0; i < MAX_CUSTOMERS_AT_ONCE; ++i)
	{
		g.customers.push_back(random_customer(names, rng));
	}
	g.ticket_inventory = random_ticket_inventory(rng);
}

// Test function to debug ticket lists
void debug_ticket_list(const vector<Ticket> &tickets)
{
	for (const auto &ticket : tickets)
	{
		ticket.test_print();
	}
}

// Initialize test data for development
void initialize_test_data()
{
	print("Initializing game with random test data...");
	std::random_device rd;
	std::mt19937 rng(rd());
	NameLists names = read_customer_names("customer_names.txt");
	fill_game_with_random_data(game_data, names, rng);
	print("Customers:");
	for (const auto& c : game_data.customers) {
		print("- " + c.name + ", $" + std::to_string(c.money) + ", " + c.preferred_ticket_class);
	}
	print("Tickets:");
	for (const auto& t : game_data.ticket_inventory) {
		print("- " + t.route + ", $" + std::to_string(t.price_paid));
	}

	//Do an autosave to save the test values
	autosaveGameData(game_data);

	//Reset the game_data back to default
	game_data = Game();

	print("Test initialization complete. Game interface starting...\n");
}

int main(int argc, char *argv[])
{
	try
	{
		// Initialize test data (remove this in production)
		//initialize_test_data();

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