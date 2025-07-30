#pragma once

#include "../menus/menu_system.h"

/**
 * TicketsForSaleApp - Clean application manager
 *
 * Handles the main game loop and menu navigation using the FTXUI-based menu system.
 * Replaces the complex switch-statement approach with a cleaner event-driven design.
 */
class TicketsForSaleApp
{
public:
    TicketsForSaleApp();
    ~TicketsForSaleApp();

    // Main application entry point
    int run();

private:
    bool running;
    int current_menu;

    // Clean menu navigation methods
    void handle_menu_transition(int menu_result);
    void initialize_game();
    void cleanup();

    // Menu handlers - much cleaner than switch statements
    int handle_main_menu();
    int handle_ticket_counter();
    int handle_inventory();
    int handle_purchase();
    int handle_barter();
    int handle_statistics();
    int handle_save_game();
    int handle_load_game();
};
