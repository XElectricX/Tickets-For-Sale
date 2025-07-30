#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <vector>
#include <string>
#include "menu_system.h"
#include "base_menu.h"
#include "code/game.h"

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
        add_option("Save Game", 'g', MENU_SAVE_GAME);
        add_option("Back to Main Menu", 'b', MENU_START_GAME); // Changed to go back to main menu properly

        // Copilot: Status info now shown in status bar below, using game_data fields

        set_footer("Use arrow keys, hotkeys [I/P/S/T/G/B], or Enter to select");
        set_theme_colors(Color::Green, Color::White, Color::Yellow, Color::Cyan);
    }

protected:
    Element create_status_bar() override
    {
        // Copilot: Show business name, player name, money, and statistics
        std::string profit = std::to_string(game_data.total_revenue - game_data.total_expenses);
        return vbox({
            hbox({
                text("🏢 Business: " + game_data.business_name) | color(Color::Cyan),
                text("  |  "),
                text("🧑 Player: " + game_data.player_name) | color(Color::White),
                text("  |  "),
                text("💰 Money: $" + std::to_string(game_data.money)) | color(Color::Green)
            }) | center,
            hbox({
                text("👥 Customers: " + std::to_string(game_data.total_customers)) | color(Color::Blue),
                text("  |  "),
                text("🎟️ Sold: " + std::to_string(game_data.total_tickets_sold)) | color(Color::Yellow),
                text("  |  "),
                text("🛒 Purchased: " + std::to_string(game_data.total_tickets_bought)) | color(Color::Magenta)
            }) | center,
            hbox({
                text("� Revenue: $" + std::to_string(game_data.total_revenue)) | color(Color::Green),
                text("  |  "),
                text("💸 Expenses: $" + std::to_string(game_data.total_expenses)) | color(Color::Red),
                text("  |  "),
                text("📈 Profit: $" + profit) | color(Color::Cyan)
            }) | center
        });
    }
};

int show_ticket_counter_menu()
{
    TicketCounterMenu menu;
    return menu.show();
}
