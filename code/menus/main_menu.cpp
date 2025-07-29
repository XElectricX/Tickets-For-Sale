#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <vector>
#include <string>
#include "menu_system.h"
#include "base_menu.h"

using namespace ftxui;

class MainMenu : public BaseMenu
{
public:
  MainMenu() : BaseMenu("🎫 TICKETS FOR SALE 🎫", "Welcome to the Ticket Trading Game", "main_menu")
  {
    // Add menu options with hotkeys
    add_option("Start New Game", 'n', MENU_TICKET_COUNTER); // Fixed: should go to ticket counter, not MENU_START_GAME
    add_option("Load Game", 'l', MENU_LOAD_GAME);
    add_option("Options", 'o', MENU_OPTIONS);
    add_option("Exit", 'q', MENU_EXIT);

    set_footer("Use arrow keys, hotkeys [N/L/O/Q], or Enter to select");
    set_theme_colors(Color::Cyan, Color::White, Color::Yellow, Color::Green);
  }

protected:
  Element create_header() override
  {
    return vbox({text("🎫 TICKETS FOR SALE 🎫") | bold | center | color(Color::Cyan),
                 text("Welcome to the Ticket Trading Game") | center | color(Color::White),
                 separator(),
                 text("Build your ticket empire by buying low and selling high!") | dim | center});
  }
};

int show_main_menu()
{
  MainMenu menu;
  return menu.show();
}
