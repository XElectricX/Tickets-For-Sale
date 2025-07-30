#include "tickets_for_sale_app.h"
#include <iostream>

TicketsForSaleApp::TicketsForSaleApp()
	: running(true), current_menu(MENU_START_GAME)
{
}

TicketsForSaleApp::~TicketsForSaleApp()
{
	cleanup();
}

int TicketsForSaleApp::run()
{
	initialize_game();

	while (running)
	{
		int menu_result = 0;

		switch (current_menu)
		{
		case MENU_START_GAME:
			menu_result = handle_main_menu();
			break;

		case MENU_TICKET_COUNTER:
			menu_result = handle_ticket_counter();
			break;

		case MENU_INVENTORY:
			menu_result = handle_inventory();
			break;

		case MENU_PURCHASE:
			menu_result = handle_purchase();
			break;

		case MENU_BARTER:
			menu_result = handle_barter();
			break;

		case MENU_STATISTICS:
			menu_result = handle_statistics();
			break;

		case MENU_SAVE_GAME:
			menu_result = handle_save_game();
			break;

		case MENU_LOAD_GAME:
			menu_result = handle_load_game();
			break;

		case MENU_EXIT:
			std::cout << "Thanks for playing Tickets for Sale!" << std::endl;
			running = false;
			return 0;

		default:
			std::cout << "Invalid menu state, exiting..." << std::endl;
			running = false;
			break;
		}

		handle_menu_transition(menu_result);
	}

	return 0;
}

void TicketsForSaleApp::initialize_game()
{
	std::cout << "=== TICKETS FOR SALE GAME ===" << std::endl;
	std::cout << "Initializing game..." << std::endl;
}

void TicketsForSaleApp::cleanup()
{
	// Clean up any resources if needed
}

void TicketsForSaleApp::handle_menu_transition(int menu_result)
{
	switch (menu_result)
	{
	case MENU_BACK:
		// Go back to main menu from any submenu
		current_menu = MENU_START_GAME;
		break;

	case MENU_EXIT:
		running = false;
		break;

	default:
		// Direct menu transition
		current_menu = menu_result;
		break;
	}
}

// Clean menu handler implementations
int TicketsForSaleApp::handle_main_menu()
{
	return show_main_menu();
}

int TicketsForSaleApp::handle_ticket_counter()
{
	return show_ticket_counter_menu();
}

int TicketsForSaleApp::handle_inventory()
{
	return show_ticket_inventory_menu();
}

int TicketsForSaleApp::handle_purchase()
{
	return show_ticket_purchasing_menu();
}

int TicketsForSaleApp::handle_barter()
{
	return show_barter_menu();
}

int TicketsForSaleApp::handle_statistics()
{
	return show_statistics_menu();
}

int TicketsForSaleApp::handle_save_game()
{
	std::cout << "Saving game..." << std::endl;
	// Implement save functionality
	return MENU_START_GAME; // Return to main menu
}

int TicketsForSaleApp::handle_load_game()
{
	std::cout << "Loading game..." << std::endl;
	// Implement load functionality
	return MENU_TICKET_COUNTER; // Go to game after loading
}
