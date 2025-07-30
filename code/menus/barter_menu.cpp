#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <vector>
#include <string>
#include "menu_system.h"
#include "base_menu.h"

using namespace ftxui;

class BarterMenu : public BaseMenu
{
public:
    BarterMenu() : BaseMenu("🤝 BARTER & SALES", "Customer Negotiations")
    {
        add_option("Negotiate with Sarah", 's', MENU_BARTER);
        add_option("Negotiate with Mike", 'm', MENU_BARTER);
        add_option("Negotiate with Jenny", 'j', MENU_BARTER);
        add_option("Negotiate with Bob", 'o', MENU_BARTER);
        add_option("View Sales History", 'h', MENU_BARTER);
        add_option("Back to Counter", 'b', MENU_TICKET_COUNTER); // Changed to go back to ticket counter

        set_footer("Use arrow keys, hotkeys [S/M/J/O/H/B], or Enter to select");
        set_theme_colors(Color::Green, Color::White, Color::Yellow, Color::Cyan);
    }

protected:
    Element create_menu_content() override
    {
        // Current customers waiting
        std::vector<std::string> customers = {
            "Sarah - Wants: Concert Tickets (Willing to pay: $50)",
            "Mike - Wants: Movie Tickets (Willing to pay: $18)",
            "Jenny - Wants: Sports Tickets (Willing to pay: $35)",
            "Bob - Wants: Theater Tickets (Willing to pay: $80)"};

        // Create customer list display
        Elements customer_elements;
        for (const auto &customer : customers)
        {
            customer_elements.push_back(text("• " + customer));
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
        return hbox({text("💰 Today's Sales: $" + std::to_string(g_game_state.daily_revenue)) | color(Color::Green),
                     text("  |  "),
                     text("👥 Customers Served: " + std::to_string(g_game_state.tickets_sold_today)) | color(Color::Blue),
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
