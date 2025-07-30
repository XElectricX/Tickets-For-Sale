#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <vector>
#include <string>
#include "menu_system.h"
#include "base_menu.h"

using namespace ftxui;

class TicketCounterMenu : public BaseMenu
{
public:
    TicketCounterMenu() : BaseMenu("🎫 TICKET COUNTER 🎫", "Your Ticket Trading Hub", "ticket_counter_menu")
    {
        // Add menu options with intuitive hotkeys
        add_option("View Ticket Inventory", 'i', MENU_INVENTORY);
        add_option("Purchase New Tickets", 'p', MENU_PURCHASE);
        add_option("Sell Tickets (Barter)", 's', MENU_BARTER);
        add_option("View Sales Statistics", 't', MENU_STATISTICS);
        add_option("Save Game", 'g', MENU_SAVE_GAME);
        add_option("Back to Main Menu", 'b', MENU_START_GAME); // Changed to go back to main menu properly

        // Add dynamic status information from game state
        add_status_info("Cash: $" + std::to_string(g_game_state.cash));
        add_status_info("Tickets in Stock: " + std::to_string(g_game_state.tickets_in_stock));
        add_status_info("Today's Sales: $" + std::to_string(g_game_state.daily_revenue));

        set_footer("Use arrow keys, hotkeys [I/P/S/T/G/B], or Enter to select");
        set_theme_colors(Color::Green, Color::White, Color::Yellow, Color::Cyan);
    }

protected:
    Element create_status_bar() override
    {
        return vbox({hbox({text("💰 Cash: $" + std::to_string(g_game_state.cash)) | color(Color::Green),
                           text("  |  "),
                           text("📦 Stock: " + std::to_string(g_game_state.tickets_in_stock)) | color(Color::Blue),
                           text("  |  "),
                           text("📈 Today: $" + std::to_string(g_game_state.daily_revenue)) | color(Color::Yellow)}) |
                         center,
                     text("Customers served today: " + std::to_string(g_game_state.tickets_sold_today)) | dim | center});
    }
};

int show_ticket_counter_menu()
{
    TicketCounterMenu menu;
    return menu.show();
}
