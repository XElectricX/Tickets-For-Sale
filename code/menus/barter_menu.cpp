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
        add_status_info("🏢 Business: " + game_data.business_name);
        add_status_info("🧑 Player: " + game_data.player_name);
        add_status_info("💰 Money: $" + std::to_string(game_data.money));
        add_status_info("🎟️ Total Sold: " + std::to_string(game_data.total_tickets_sold));

        // Add an option for each customer
        int idx = 0;
        for (const auto &customer : game_data.customers)
        {
            // Use a unique hotkey for each customer (first letter or fallback to number)
            char hotkey = customer.name.empty() ? ('1' + idx) : customer.name[0];
            add_option("Sell to " + customer.name + " (Wants: " + customer.preferred_ticket_class + ")", hotkey, 100 + idx, [this, idx]() { handle_customer_selection(idx); });
            ++idx;
        }
        add_option("View Sales History", 'h', MENU_BARTER);
        add_option("Back to Counter", 'b', MENU_TICKET_COUNTER);

        set_footer("Select a customer to sell a ticket, or ESC/B to go back");
        set_theme_colors(Color::Green, Color::White, Color::Yellow, Color::Cyan);
    }

    void handle_customer_selection(int customer_index)
    {
        if (customer_index < 0 || customer_index >= static_cast<int>(game_data.customers.size()))
            return;

        Customer& customer = game_data.customers[customer_index];

        // Convert preferred_ticket_class string to Ticket_Class enum
        Ticket_Class desired_class = Ticket_Class::TICKET_CLASS_ECONOMY;
        if (customer.preferred_ticket_class == "Economy")
            desired_class = Ticket_Class::TICKET_CLASS_ECONOMY;
        else if (customer.preferred_ticket_class == "Business")
            desired_class = Ticket_Class::TICKET_CLASS_BUSINESS;
        else if (customer.preferred_ticket_class == "Luxury")
            desired_class = Ticket_Class::TICKET_CLASS_LUXURY;

        // Find a ticket in inventory matching the desired class
        auto it = std::find_if(game_data.ticket_inventory.begin(), game_data.ticket_inventory.end(),
            [desired_class](const Ticket& t) { return t.ticket_class == desired_class; });

        if (it == game_data.ticket_inventory.end())
        {
            // No matching ticket, do nothing
            return;
        }

        // Sell the ticket: add money, remove ticket, remove customer
        int sale_price = it->price_paid; // You can adjust this logic as needed
        game_data.money += sale_price;
        game_data.total_tickets_sold++;
        game_data.total_revenue += sale_price;
        game_data.ticket_inventory.erase(it);
        game_data.customers.erase(game_data.customers.begin() + customer_index);

        // Optionally, refresh the menu (rebuild options)
        options.clear();
        add_status_info("🏢 Business: " + game_data.business_name);
        add_status_info("🧑 Player: " + game_data.player_name);
        add_status_info("💰 Money: $" + std::to_string(game_data.money));
        add_status_info("🎟️ Total Sold: " + std::to_string(game_data.total_tickets_sold));
        int idx = 0;
        for (const auto &c : game_data.customers)
        {
            char hotkey = c.name.empty() ? ('1' + idx) : c.name[0];
            add_option("Sell to " + c.name + " (Wants: " + c.preferred_ticket_class + ")", hotkey, 100 + idx, [this, idx]() { handle_customer_selection(idx); });
            ++idx;
        }
        add_option("View Sales History", 'h', MENU_BARTER);
        add_option("Back to Counter", 'b', MENU_TICKET_COUNTER);
    }

protected:
    Element create_menu_content() override
    {
        // Use the actual customer list from game_data
        Elements customer_elements;
        for (const auto &customer : game_data.customers)
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
