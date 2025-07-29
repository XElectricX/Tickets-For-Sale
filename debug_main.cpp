#include <iostream>
#include <string>
#include <vector>
#include "code/helpers.h"
#include "code/objects/tickets.h"
#include "code/defines.h"
#include "code/menus/menu_system.h"

using std::string;
using std::to_string;

// Simple test function to debug menu return values
void test_menu_returns()
{
    std::cout << "=== MENU SYSTEM DEBUG ===" << std::endl;

    std::cout << "Testing menu constants:" << std::endl;
    std::cout << "MENU_START_GAME = " << MENU_START_GAME << std::endl;
    std::cout << "MENU_TICKET_COUNTER = " << MENU_TICKET_COUNTER << std::endl;
    std::cout << "MENU_EXIT = " << MENU_EXIT << std::endl;
    std::cout << "MENU_BACK = " << MENU_BACK << std::endl;

    std::cout << "\nTesting main menu..." << std::endl;
    int result = show_main_menu();
    std::cout << "Main menu returned: " << result << std::endl;

    if (result == MENU_TICKET_COUNTER)
    {
        std::cout << "\nTesting ticket counter menu..." << std::endl;
        int counter_result = show_ticket_counter_menu();
        std::cout << "Ticket counter menu returned: " << counter_result << std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::cout << "=== TICKETS FOR SALE GAME - DEBUG MODE ===" << std::endl;

    // Test the menu system
    test_menu_returns();

    return 0;
}
