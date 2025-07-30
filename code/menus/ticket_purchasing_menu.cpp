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

        //Add business, player, money, and total tickets purchased
        add_status_info("🏢 Business: " + game_data.business_name);
        add_status_info("🧑 Player: " + game_data.player_name);
        add_status_info("💰 Money: $" + std::to_string(game_data.money));
        add_status_info("🛒 Total Purchased: " + std::to_string(game_data.total_tickets_bought));

        set_footer("Use arrow keys, hotkeys [C/M/S/T/F/H/B], or Enter to select");
        set_theme_colors(Color::Green, Color::White, Color::Yellow, Color::Cyan);
    }

protected:
    Element create_menu_content() override
    {
        //Display tickets available for purchase from tickets_for_sale
        Elements ticket_elements;
        for (const auto &datum : game_data.tickets_for_sale)
        {
            std::string info = datum.route + " ($" + std::to_string(datum.price) + " each) - Available: " + std::to_string(datum.amount_available);
            ticket_elements.push_back(text("• " + info));
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
