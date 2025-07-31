#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
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
        for (size_t i = 0; i < game_data.customers.size(); ++i)
        {
            const auto &customer = game_data.customers[i];
            // Use a unique hotkey for each customer (first letter or fallback to number)
            char hotkey = customer.name.empty() ? ('1' + idx) : customer.name[0];
            add_option("Sell to " + customer.name + " (Wants: " + customer.preferred_ticket_class + ")", hotkey, MENU_BARTER, [this, i]()
                       { handle_customer_selection(static_cast<int>(i)); });
            ++idx;
        }
        add_option("View Sales History", 'h', 2000); // Special return code for sales history
        add_option("Back to Counter", 'b', MENU_TICKET_COUNTER);

        set_footer("Select a customer to sell a ticket, or ESC/B to go back");
        set_theme_colors(Color::Green, Color::White, Color::Yellow, Color::Cyan);
    }

    void handle_customer_selection(int customer_index)
    {
        if (customer_index < 0 || customer_index >= static_cast<int>(game_data.customers.size()))
            return;

        Customer &customer = game_data.customers[customer_index];

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
                               [desired_class](const Ticket &t)
                               { return t.ticket_class == desired_class; });

        if (it == game_data.ticket_inventory.end())
        {
            // No matching ticket, provide user feedback
            // No matching ticket, provide user feedback
            return;
        }

        // Sell the ticket: add money, remove ticket, remove customer
        int sale_price = it->price_paid; // You can adjust this logic as needed
        game_data.money += sale_price;
        game_data.total_tickets_sold++;
        game_data.total_revenue += sale_price;
        game_data.ticket_inventory.erase(it);
        game_data.customers.erase(game_data.customers.begin() + customer_index);

        // Refresh the menu (rebuild options)
        refresh_menu_options();
    }

    void show_sales_history()
    {
        // Clear current status info and show sales history
        status_info.clear();
        add_status_info("📊 SALES HISTORY SUMMARY:");
        add_status_info("🎟️ Total Tickets Sold: " + std::to_string(game_data.total_tickets_sold));
        add_status_info("💰 Total Revenue: $" + std::to_string(game_data.total_revenue));
        add_status_info("💸 Total Expenses: $" + std::to_string(game_data.total_expenses));
        add_status_info("📈 Net Profit: $" + std::to_string(game_data.total_revenue - game_data.total_expenses));
        add_status_info("👥 Total Customers Served: " + std::to_string(game_data.total_customers));

        if (game_data.total_tickets_sold > 0)
        {
            int avg_sale_price = game_data.total_revenue / game_data.total_tickets_sold;
            add_status_info("📊 Average Sale Price: $" + std::to_string(avg_sale_price));
        }

        add_status_info(""); // Empty line for spacing
        add_status_info("Press 'r' to return to normal view...");

        // Add a return option
        options.clear();
        add_option("Return to Customer List", 'r', MENU_BARTER, [this]()
                   { refresh_menu_options(); });
        add_option("Back to Counter", 'b', MENU_TICKET_COUNTER);
    }

    void refresh_menu_options()
    {
        options.clear();
        status_info.clear(); // Clear status info first
        add_status_info("🏢 Business: " + game_data.business_name);
        add_status_info("🧑 Player: " + game_data.player_name);
        add_status_info("💰 Money: $" + std::to_string(game_data.money));
        add_status_info("🎟️ Total Sold: " + std::to_string(game_data.total_tickets_sold));
        int idx = 0;
        for (size_t i = 0; i < game_data.customers.size(); ++i)
        {
            const auto &c = game_data.customers[i];
            char hotkey = c.name.empty() ? ('1' + idx) : c.name[0];
            add_option("Sell to " + c.name + " (Wants: " + c.preferred_ticket_class + ")", hotkey, MENU_BARTER, [this, i]()
                       { handle_customer_selection(static_cast<int>(i)); });
            ++idx;
        }
        add_option("View Sales History", 'h', 2000); // Special return code for sales history
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
                     text("💼 Active Negotiations: " + std::to_string(game_data.customers.size())) | color(Color::Yellow)}) |
               center;
    }
};

int show_barter_menu()
{
    while (true)
    {
        BarterMenu menu;
        int result = menu.show();

        if (result == 2000)
        {
            // Show simple sales history
            system("cls"); // Clear screen on Windows
            std::cout << "\n📊 SALES HISTORY SUMMARY\n";
            std::cout << "============================\n";
            std::cout << "🎟️ Total Tickets Sold: " << game_data.total_tickets_sold << "\n";
            std::cout << "💰 Total Revenue: $" << game_data.total_revenue << "\n";
            std::cout << "💸 Total Expenses: $" << game_data.total_expenses << "\n";

            int net_profit = game_data.total_revenue - game_data.total_expenses;
            std::cout << "📈 Net Profit: $" << net_profit << "\n";
            std::cout << "👥 Total Customers Served: " << game_data.total_customers << "\n";

            if (game_data.total_tickets_sold > 0)
            {
                int avg_sale_price = game_data.total_revenue / game_data.total_tickets_sold;
                std::cout << "📊 Average Sale Price: $" << avg_sale_price << "\n";
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            continue; // Return to barter menu
        }

        return result; // Return to main game
    }
}
