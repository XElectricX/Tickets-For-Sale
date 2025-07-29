#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include "menu_system.h"
#include "base_menu.h"

using namespace ftxui;

class StatisticsMenu : public BaseMenu
{
public:
    StatisticsMenu() : BaseMenu("📊 SALES STATISTICS", "Your Trading Performance")
    {
        add_option("Export Statistics", 'e', MENU_STATISTICS);
        add_option("Reset Statistics", 'r', MENU_STATISTICS, [this]()
                   { reset_stats(); });
        add_option("View Detailed Report", 'd', MENU_STATISTICS);
        add_option("Back to Ticket Counter", 'b', MENU_TICKET_COUNTER); // Changed to go back to ticket counter

        set_footer("Use arrow keys, hotkeys [E/R/D/B], or Enter to select");
        set_theme_colors(Color::Blue, Color::White, Color::Yellow, Color::Cyan);
    }

private:
    void reset_stats()
    {
        // Placeholder for statistics reset functionality
        // In a real implementation, this would reset statistics with confirmation
    }

    std::string format_currency(int amount)
    {
        return "$" + std::to_string(amount);
    }

    std::string format_percentage(float percentage)
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << percentage << "%";
        return ss.str();
    }

protected:
    Element create_header() override
    {
        return vbox({text("📊 SALES STATISTICS 📊") | bold | center | color(Color::Blue),
                     text("Your Trading Performance") | center | color(Color::White),
                     separator(),
                     text("Track your progress and identify opportunities") | dim | center});
    }

    Element create_menu_content() override
    {
        // Calculate profit and profit margin
        int profit = g_game_state.total_revenue - g_game_state.total_expenses;
        float profit_margin = g_game_state.total_revenue > 0 ? (static_cast<float>(profit) / g_game_state.total_revenue * 100) : 0.0f;

        return vbox({// Trading Summary
                     text("📈 TRADING SUMMARY") | bold | color(Color::GreenLight),
                     separator(),
                     hbox({vbox({hbox({text("Tickets Sold: ") | color(Color::BlueLight),
                                       text(std::to_string(g_game_state.total_tickets_sold)) | bold}),
                                 hbox({text("Tickets Bought: ") | color(Color::BlueLight),
                                       text(std::to_string(g_game_state.total_tickets_bought)) | bold}),
                                 hbox({text("Net Tickets: ") | color(Color::BlueLight),
                                       text(std::to_string(g_game_state.total_tickets_bought - g_game_state.total_tickets_sold)) | bold})}) |
                               flex,
                           separator(),
                           vbox({hbox({text("Total Revenue: ") | color(Color::GreenLight),
                                       text(format_currency(g_game_state.total_revenue)) | bold | color(Color::Green)}),
                                 hbox({text("Total Expenses: ") | color(Color::RedLight),
                                       text(format_currency(g_game_state.total_expenses)) | bold | color(Color::Red)}),
                                 hbox({text("Net Profit: ") | color(profit >= 0 ? Color::GreenLight : Color::RedLight),
                                       text(format_currency(profit)) | bold | color(profit >= 0 ? Color::Green : Color::Red)})}) |
                               flex}),
                     separator(),

                     // Performance Metrics
                     text("🎯 PERFORMANCE METRICS") | bold | color(Color::YellowLight),
                     separator(),
                     hbox({vbox({hbox({text("Average Markup: ") | color(Color::YellowLight),
                                       text(format_percentage(g_game_state.average_markup)) | bold}),
                                 hbox({text("Profit Margin: ") | color(Color::YellowLight),
                                       text(format_percentage(profit_margin)) | bold})}) |
                               flex,
                           separator(),
                           vbox({text("Most Popular Ticket:") | color(Color::YellowLight),
                                 text(g_game_state.most_popular_ticket) | bold | color(Color::Cyan)}) |
                               flex}),
                     separator(),

                     // Today's Performance
                     text("📅 TODAY'S PERFORMANCE") | bold | color(Color::MagentaLight),
                     separator(),
                     hbox({hbox({text("Revenue: ") | color(Color::MagentaLight),
                                 text(format_currency(g_game_state.daily_revenue)) | bold}),
                           text("  |  "),
                           hbox({text("Customers: ") | color(Color::MagentaLight),
                                 text(std::to_string(g_game_state.tickets_sold_today)) | bold}),
                           text("  |  "),
                           hbox({text("Cash: ") | color(Color::MagentaLight),
                                 text(format_currency(g_game_state.cash)) | bold})}) |
                         center,
                     separator(),

                     // Menu options
                     text("📋 ACTIONS") | bold | color(Color::White),
                     separator(),
                     BaseMenu::create_menu_content()});
    }
};

int show_statistics_menu()
{
    StatisticsMenu menu;
    return menu.show();
}
