#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <vector>
#include <string>
#include "menu_system.h"

using namespace ftxui;

int show_statistics_menu() {
    // Stats data (in a real implementation, this would come from the game state)
    int tickets_sold = 152;
    int tickets_bought = 199;
    int revenue = 15250;
    int expenses = 9950;
    int profit = revenue - expenses;
    float avg_markup = 27.5f;
    std::string most_popular = "Business Class - Tokyo to London";

    // Create a back button
    std::string back_label = "Back to Ticket Counter";
    auto back_button = Button(&back_label, [&] { return true; });

    // Container with just the back button
    auto container = Container::Vertical({
        back_button,
    });

    bool exit_menu = false;
    back_button->on_click = [&] {
        exit_menu = true;
        return true;
    };

    auto screen = ScreenInteractive::TerminalOutput();

    auto renderer = Renderer(container, [&] {
        return vbox({
            text("📊 SALES STATISTICS 📊") | bold | center,
            separator(),
            vbox({
                hbox({
                    text("Tickets Sold: ") | color(Color::BlueLight),
                    text(std::to_string(tickets_sold))
                }),
                hbox({
                    text("Tickets Bought: ") | color(Color::BlueLight),
                    text(std::to_string(tickets_bought))
                }),
                separator(),
                hbox({
                    text("Total Revenue: ") | color(Color::GreenLight),
                    text("$" + std::to_string(revenue))
                }),
                hbox({
                    text("Total Expenses: ") | color(Color::RedLight),
                    text("$" + std::to_string(expenses))
                }),
                hbox({
                    text("Net Profit: ") | color(profit >= 0 ? Color::Green : Color::Red),
                    text("$" + std::to_string(profit))
                }),
                separator(),
                hbox({
                    text("Average Markup: ") | color(Color::YellowLight),
                    text(std::to_string(avg_markup) + "%")
                }),
                hbox({
                    text("Most Popular Ticket: ") | color(Color::YellowLight),
                    text(most_popular)
                }),
            }) | border,
            filler(),
            container->Render(),
            separator(),
            text("Press Enter to return to the Ticket Counter") | dim | center
        }) | border;
    });

    // Exit the menu loop when back button is clicked
    container->on_change = [&] {
        if (exit_menu) {
            screen.ExitLoopClosure()();
        }
    };

    screen.Loop(renderer);

    // Return to ticket counter
    return MENU_BACK;
}
