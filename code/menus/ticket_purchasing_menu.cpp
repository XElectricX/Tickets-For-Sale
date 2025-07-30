#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <vector>
#include <string>
#include "menu_system.h"
#include "base_menu.h"

using namespace ftxui;

// Sample ticket data - in a real implementation this would come from game state
std::vector<std::string> available_tickets = {
    "Concert Tickets - Rock Festival ($35 each) - Available: 50",
    "Movie Tickets - New Release ($12 each) - Available: 100",
    "Sports Tickets - Football Game ($25 each) - Available: 30",
    "Theater Tickets - Musical ($60 each) - Available: 15",
    "Festival Passes - Food Festival ($20 each) - Available: 75"};

class TicketPurchasingMenu : public BaseMenu
{
public:
    TicketPurchasingMenu() : BaseMenu("💳 TICKET PURCHASING 💳", "Buy Tickets from Suppliers", "ticket_purchasing_menu")
    {
        add_option("Purchase Concert Tickets", 'c', MENU_PURCHASE);
        add_option("Purchase Movie Tickets", 'm', MENU_PURCHASE);
        add_option("Purchase Sports Tickets", 's', MENU_PURCHASE);
        add_option("Purchase Theater Tickets", 't', MENU_PURCHASE);
        add_option("Purchase Festival Passes", 'f', MENU_PURCHASE);
        add_option("View Purchase History", 'h', MENU_PURCHASE);
        add_option("Back to Counter", 'b', MENU_TICKET_COUNTER); // Changed to go back to ticket counter

        add_status_info("Funds: $5,000");
        add_status_info("Storage Space: 84%");

        set_footer("Use arrow keys, hotkeys [C/M/S/T/F/H/B], or Enter to select");
        set_theme_colors(Color::Green, Color::White, Color::Yellow, Color::Cyan);
    }

protected:
    Element create_menu_content() override
    {
        // Create available tickets display
        Elements ticket_elements;
        for (const auto &ticket : available_tickets)
        {
            ticket_elements.push_back(text("• " + ticket));
        }

        return vbox({text("Available from Suppliers:") | bold,
                     vbox(ticket_elements) | border,
                     separator(),
                     text("Purchase Options:") | bold,
                     BaseMenu::create_menu_content()});
    }
};

int show_ticket_purchasing_menu()
{
    TicketPurchasingMenu menu;
    return menu.show();
}
