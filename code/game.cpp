#include "game.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "menus/menu_system.h"

using namespace ftxui;

// Check if the player is bankrupt (has no money and no sellable assets)
bool is_game_bankrupt()
{
    // If player has money, they're not bankrupt
    if (game_data.money > 0)
        return false;

    // If player has no money, check if they have any tickets to sell
    if (game_data.ticket_inventory.empty())
        return true; // No money and no tickets = bankrupt

    // Player has tickets but no money - they can still potentially sell tickets
    return false;
}

// Show bankruptcy screen and return to main menu
int show_bankruptcy_screen()
{
    auto screen = ScreenInteractive::TerminalOutput();

// Clear screen
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    bool exit_pressed = false;

    auto component = Renderer([&]
                              { return vbox({text("💸 BANKRUPTCY! 💸") | bold | center | color(Color::Red),
                                             separator(),
                                             text("Your business has run out of money!") | center | color(Color::White),
                                             text("") | center,
                                             text("📊 FINAL STATISTICS:") | bold | center | color(Color::Yellow),
                                             text("🏢 Business: " + game_data.business_name) | center,
                                             text("🧑 Player: " + game_data.player_name) | center,
                                             text("💰 Final Money: $" + std::to_string(game_data.money)) | center | color(Color::Red),
                                             text("🎟️ Total Tickets Sold: " + std::to_string(game_data.total_tickets_sold)) | center,
                                             text("🛒 Total Tickets Bought: " + std::to_string(game_data.total_tickets_bought)) | center,
                                             text("💰 Total Revenue: $" + std::to_string(game_data.total_revenue)) | center | color(Color::Green),
                                             text("💸 Total Expenses: $" + std::to_string(game_data.total_expenses)) | center | color(Color::Red),
                                             text("📈 Net Profit/Loss: $" + std::to_string(game_data.total_revenue - game_data.total_expenses)) | center |
                                                 ((game_data.total_revenue - game_data.total_expenses >= 0) ? color(Color::Green) : color(Color::Red)),
                                             text("") | center,
                                             text("Thank you for playing Tickets for Sale!") | center | color(Color::Cyan),
                                             text("") | center,
                                             text("Press any key to return to main menu...") | center | color(Color::GrayLight)}) |
                                       border | center; });

    // Add event handling
    auto event_handler = CatchEvent(component, [&](Event event)
                                    {
        if (event.is_character() || event == Event::Return || event == Event::Escape) {
            exit_pressed = true;
            screen.ExitLoopClosure()();
            return true;
        }
        return false; });

    screen.Loop(event_handler);

    // Reset game data for new game
    game_data = Game();

    return MENU_START_GAME; // Return to main menu
}
