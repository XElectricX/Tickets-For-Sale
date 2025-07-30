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

class TicketInventoryMenu : public BaseMenu
{
public:
    TicketInventoryMenu() : BaseMenu("📦 TICKET INVENTORY 📦", "Manage Your Tickets", "ticket_inventory_menu")
    {
        add_option("View Ticket Details", 'v', MENU_INVENTORY);
        add_option("Sort by Price", 'p', MENU_INVENTORY);
        add_option("Sort by Stock", 's', MENU_INVENTORY);
        add_option("Back to Counter", 'b', MENU_TICKET_COUNTER); // Changed to go back to ticket counter

        add_status_info("Total Value: $1,847");
        add_status_info("Items: 66");

        set_footer("Use arrow keys, hotkeys [V/P/S/B], or Enter to select");
        set_theme_colors(Color::Blue, Color::White, Color::Yellow, Color::Green);
    }

protected:
    Element create_menu_content() override
    {
        //Display tickets from the player's inventory
        Elements ticket_elements;
        for (const auto &ticket : game_data.ticket_inventory)
        {
            std::string info = ticket.route + " ($" + std::to_string(ticket.price_paid) + ") - Class: " + std::to_string(static_cast<int>(ticket.ticket_class));
            ticket_elements.push_back(text("• " + info));
        }

        return vbox({text("Current Stock:") | bold,
                     vbox(ticket_elements) | border,
                     separator(),
                     text("Actions:") | bold,
                     BaseMenu::create_menu_content()});
    }
};

int show_ticket_inventory_menu()
{
    TicketInventoryMenu menu;
    return menu.show();
}
