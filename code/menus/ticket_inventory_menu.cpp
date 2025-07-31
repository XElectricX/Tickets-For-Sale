#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <vector>
#include <string>
#include "menu_system.h"
#include "base_menu.h"
#include "code/game.h"
#include "code/defines.h"

using namespace ftxui;

class TicketInventoryMenu : public BaseMenu
{
public:
    TicketInventoryMenu() : BaseMenu("📦 TICKET INVENTORY 📦", "Manage Your Tickets", "ticket_inventory_menu")
    {
        add_option("View Ticket Details", 'v', MENU_INVENTORY);
        add_option("Sort by Price", 'p', MENU_INVENTORY);
        add_option("Sort by Stock", 's', MENU_INVENTORY);
        add_option("Back to Counter", 'b', MENU_TICKET_COUNTER);

        // Calculate dynamic status information
        int total_value = 0;
        for (const auto &ticket : game_data.ticket_inventory)
        {
            total_value += ticket.price_paid;
        }

        add_status_info("Total Value: $" + std::to_string(total_value));
        add_status_info("Items: " + std::to_string(game_data.ticket_inventory.size()));

        set_footer("Use arrow keys, hotkeys [V/P/S/B], or Enter to select");
        set_theme_colors(Color::Blue, Color::White, Color::Yellow, Color::Green);
    }

protected:
    Element create_menu_content() override
    {
        // Display tickets from the player's inventory
        Elements ticket_elements;

        if (game_data.ticket_inventory.empty())
        {
            ticket_elements.push_back(text("No tickets in inventory") | color(Color::GrayLight) | center);
        }
        else
        {
            for (size_t i = 0; i < game_data.ticket_inventory.size(); ++i)
            {
                const auto &ticket = game_data.ticket_inventory[i];
                std::string class_name;
                switch (ticket.ticket_class)
                {
                case Ticket_Class::TICKET_CLASS_ECONOMY:
                    class_name = "Economy";
                    break;
                case Ticket_Class::TICKET_CLASS_BUSINESS:
                    class_name = "Business";
                    break;
                case Ticket_Class::TICKET_CLASS_LUXURY:
                    class_name = "First";
                    break;
                default:
                    class_name = "Unknown";
                    break;
                }

                std::string info = std::to_string(i + 1) + ". " + ticket.route +
                                   " | $" + std::to_string(ticket.price_paid) +
                                   " | " + class_name + " Class";
                ticket_elements.push_back(text("• " + info) | color(Color::White));
            }
        }

        return vbox({text("Current Stock:") | bold | color(Color::Yellow),
                     vbox(ticket_elements) | border | color(Color::Blue),
                     separator(),
                     text("Actions:") | bold | color(Color::Green),
                     BaseMenu::create_menu_content()});
    }
};

int show_ticket_inventory_menu()
{
    TicketInventoryMenu menu;
    return menu.show();
}
