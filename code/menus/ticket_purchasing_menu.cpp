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

using namespace ftxui;

class TicketPurchasingMenu : public BaseMenu
{
public:
    TicketPurchasingMenu() : BaseMenu("💳 TICKET PURCHASING 💳", "Buy Tickets from Suppliers", "ticket_purchasing_menu")
    {
        // Add an option for each available ticket type
        int idx = 0;
        for (size_t i = 0; i < game_data.tickets_for_sale.size(); ++i)
        {
            const auto &ticket_datum = game_data.tickets_for_sale[i];
            if (ticket_datum.amount_available > 0)
            {
                char hotkey = (idx < 9) ? ('1' + idx) : ('a' + (idx - 9));
                std::string option_text = "Buy " + ticket_datum.route + " ($" + std::to_string(ticket_datum.price) + " each) - " + std::to_string(ticket_datum.amount_available) + " available";
                // Capture the actual vector index (i) instead of the display index (idx)
                add_option(option_text, hotkey, MENU_PURCHASE, [this, i]()
                           { handle_ticket_purchase(static_cast<int>(i)); });
                ++idx;
            }
        }

        add_option("View Purchase History", 'h', 1000); // Special return code for history
        add_option("Back to Counter", 'b', MENU_TICKET_COUNTER);

        // Add business, player, money, and total tickets purchased
        add_status_info("🏢 Business: " + game_data.business_name);
        add_status_info("🧑 Player: " + game_data.player_name);
        add_status_info("💰 Money: $" + std::to_string(game_data.money));
        add_status_info("🛒 Total Purchased: " + std::to_string(game_data.total_tickets_bought));

        set_footer("Select a ticket to purchase, or ESC/B to go back");
        set_theme_colors(Color::Green, Color::White, Color::Yellow, Color::Cyan);
    }

    void handle_ticket_purchase(int ticket_index)
    {
        // Safety check: ensure the index is valid
        if (ticket_index < 0 || ticket_index >= static_cast<int>(game_data.tickets_for_sale.size()))
        {
            // Index out of bounds - refresh menu and return
            refresh_menu_options();
            return;
        }

        Ticket_Datum &ticket_datum = game_data.tickets_for_sale[ticket_index];

        // Check if tickets are available
        if (ticket_datum.amount_available <= 0)
        {
            refresh_menu_options();
            return;
        }

        // Check if player has enough money
        if (game_data.money < ticket_datum.price)
        {
            // Check if player is bankrupt (no money and no tickets to sell)
            if (is_game_bankrupt())
            {
                // Game over - show bankruptcy screen
                show_bankruptcy_screen();
                return;
            }

            // Show insufficient funds message
            status_info.clear();
            add_status_info("❌ INSUFFICIENT FUNDS!");
            add_status_info("💰 You have: $" + std::to_string(game_data.money));
            add_status_info("💸 Need: $" + std::to_string(ticket_datum.price));
            add_status_info("🏢 Business: " + game_data.business_name);
            add_status_info("🧑 Player: " + game_data.player_name);
            add_status_info("");
            add_status_info("💡 Tip: Sell some tickets to customers to earn money!");
            add_status_info("Press any key to continue...");
            return;
        }

        // Purchase the ticket
        game_data.money -= ticket_datum.price;
        game_data.total_tickets_bought++;
        game_data.total_expenses += ticket_datum.price;

        // Create and add ticket to inventory
        Ticket new_ticket(ticket_datum.ticket_class, ticket_datum.price, ticket_datum.route);
        game_data.ticket_inventory.push_back(new_ticket);

        // Reduce available amount
        ticket_datum.amount_available--;

        // Refresh the menu
        refresh_menu_options();
    }

    void refresh_menu_options()
    {
        options.clear();

        // Add purchase options for available tickets
        int idx = 0;
        for (size_t i = 0; i < game_data.tickets_for_sale.size(); ++i)
        {
            const auto &ticket_datum = game_data.tickets_for_sale[i];
            if (ticket_datum.amount_available > 0)
            {
                char hotkey = (idx < 9) ? ('1' + idx) : ('a' + (idx - 9));
                std::string option_text = "Buy " + ticket_datum.route + " ($" + std::to_string(ticket_datum.price) + " each) - " + std::to_string(ticket_datum.amount_available) + " available";
                // Capture the actual vector index (i) instead of the display index (idx)
                add_option(option_text, hotkey, MENU_PURCHASE, [this, i]()
                           { handle_ticket_purchase(static_cast<int>(i)); });
                ++idx;
            }
        }

        add_option("View Purchase History", 'h', 1000); // Special return code for history
        add_option("Back to Counter", 'b', MENU_TICKET_COUNTER);

        // Update status info
        status_info.clear();
        add_status_info("🏢 Business: " + game_data.business_name);
        add_status_info("🧑 Player: " + game_data.player_name);
        add_status_info("💰 Money: $" + std::to_string(game_data.money));
        add_status_info("🛒 Total Purchased: " + std::to_string(game_data.total_tickets_bought));
    }

protected:
    Element create_menu_content() override
    {
        // Display tickets available for purchase from tickets_for_sale
        Elements ticket_elements;

        if (game_data.tickets_for_sale.empty())
        {
            ticket_elements.push_back(text("• No tickets available from suppliers") | color(Color::Red));
        }
        else
        {
            for (const auto &datum : game_data.tickets_for_sale)
            {
                std::string availability_text = datum.amount_available > 0 ? "Available: " + std::to_string(datum.amount_available) : "SOLD OUT";

                Color text_color = datum.amount_available > 0 ? Color::White : Color::Red;

                std::string info = datum.route + " ($" + std::to_string(datum.price) + " each) - " + availability_text;
                ticket_elements.push_back(text("• " + info) | color(text_color));
            }
        }

        return vbox({text("📋 AVAILABLE FROM SUPPLIERS") | bold | color(Color::GreenLight),
                     separator(),
                     vbox(ticket_elements) | border,
                     separator(),
                     text("💳 PURCHASE OPTIONS") | bold | color(Color::White),
                     separator(),
                     BaseMenu::create_menu_content()});
    }
};

int show_ticket_purchasing_menu()
{
    while (true)
    {
        TicketPurchasingMenu menu;
        int result = menu.show();

        if (result == 1000)
        {
            // Show simple purchase history
            system("cls"); // Clear screen on Windows
            std::cout << "\n📊 PURCHASE HISTORY SUMMARY\n";
            std::cout << "============================\n";
            std::cout << "🛒 Total Tickets Purchased: " << game_data.total_tickets_bought << "\n";
            std::cout << "💸 Total Expenses: $" << game_data.total_expenses << "\n";
            std::cout << "📦 Current Inventory: " << game_data.ticket_inventory.size() << " tickets\n";

            if (game_data.total_tickets_bought > 0)
            {
                int avg_price = game_data.total_expenses / game_data.total_tickets_bought;
                std::cout << "📊 Average Purchase Price: $" << avg_price << "\n";
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            continue; // Return to purchasing menu
        }

        return result; // Return to main game
    }
}
