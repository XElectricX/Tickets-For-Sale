#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <vector>
#include <string>
#include "menu_system.h"
#include "base_menu.h"
#include "code/game.h"
#include "code/objects/customers.h"

using namespace ftxui;

class BarterMenu : public BaseMenu
{
public:
    BarterMenu() : BaseMenu("🤝 BARTER & SALES", "Customer Negotiations")
    {
        // Copilot: Add business, player, money, and total tickets sold to status info
        add_status_info("🏢 Business: " + game_data.business_name);
        add_status_info("🧑 Player: " + game_data.player_name);
        add_status_info("💰 Money: $" + std::to_string(game_data.money));
        add_status_info("🎟️ Total Sold: " + std::to_string(game_data.total_tickets_sold));

        //Iterate through available customers and add options
        for (const auto &customer : game_data.customers)
        {
            add_option("Negotiate with " + customer.name, customer.name[0], MENU_BARTER);
        }
        add_option("View Sales History", 'h', MENU_BARTER);
        add_option("Back to Counter", 'b', MENU_TICKET_COUNTER);

        set_footer("Use arrow keys, hotkeys [S/M/J/O/H/B], or Enter to select");
        set_theme_colors(Color::Green, Color::White, Color::Yellow, Color::Cyan);
    }

protected:
    Element create_menu_content() override
    {

        // Copilot: Use the new Customer class for customer data
        #include "code/objects/customers.h"
        std::vector<Customer> customers = {
            Customer("Sarah", 50.0, 28, 100, 2, "Concert", 3, 4),
            Customer("Mike", 18.0, 22, 90, 1, "Movie", 2, 2),
            Customer("Jenny", 35.0, 31, 120, 3, "Sports", 4, 5),
            Customer("Bob", 80.0, 45, 110, 1, "Theater", 1, 3)
        };

        // Create customer list display
        Elements customer_elements;
        for (const auto &customer : customers)
        {
            std::string info = customer.name + " - Wants: " + customer.preferred_ticket_class + " Tickets (Willing to pay: $" + std::to_string(static_cast<int>(customer.money)) + ")";
            customer_elements.push_back(text("• " + info));
        }

        return vbox({text("👥 CUSTOMERS WAITING") | bold | color(Color::GreenLight),
                     separator(),
                     vbox(customer_elements) | border,
                     separator(),
                     text("📋 ACTIONS") | bold | color(Color::White),
                     separator(),
                     BaseMenu::create_menu_content()});
    }

    Element create_status_bar() override
    {
        return hbox({text("💰 Total Revenue: $" + std::to_string(game_data.total_revenue)) | color(Color::Green),
                     text("  |  "),
                     text("👥 Customers Served: " + std::to_string(game_data.total_customers)) | color(Color::Blue),
                     text("  |  "),
                     text("💼 Active Negotiations: 4") | color(Color::Yellow)}) |
               center;
    }
};

int show_barter_menu()
{
    BarterMenu menu;
    return menu.show();
}
