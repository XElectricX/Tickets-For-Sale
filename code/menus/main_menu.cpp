#include <iostream>
#include <string>
#include "code/save_system.h"
#include "code/helpers.h"
#include "code/menus/main_menu.h"
#include "code/defines.h"
#include "code/menus/save_system_menus.h"

using std::string;
using std::to_string;

// Global list of existing menu objects
vector<Menu *> menu_list;

// Menu
void Menu::run()
{
  while (true)
  {
    // Clear the terminal
    system("cls");
    print("\n--- " + title + " ---\n");

    display_choices();

    print("Awaiting choice: ", false);
    unsigned short int choice = 0;
    while (!choice)
    {
      try
      {
        short_int_input(choice);

        if (choice > options.size())
        {
          print("\r" + string(50, ' ') + "\r");
          continue;
        }

        pick_choice(choice);
      }

      catch (const std::exception &e)
      {
        // Delete the invalid input the user just entered
        print("\r" + string(50, ' ') + "\r");
        continue;
      }
    }
  }
}

// Display menu options
void Menu::display_choices()
{
  for (size_t i = 0; i < options.size(); ++i)
  {
    print(to_string(i + 1) + ". " + options[i]);
  }

  print("0. " + zero_option);
}

// Always override this for each type of menu; input validation should be handled in run()
void Menu::pick_choice(int choice)
{
  // Switch() breaks when used here, using if statements instead
  if (choice == 0)
  {
    on_zero_option();
    return;
  }

  if (choice == 1)
  {
    // Load last saved game or autosave
    // Do later
    return;
  }

  if (choice == 2)
  {
    Menu menu = create_or_switch_menu(LOAD_SLOT_MENU);
    menu.run();
    return;
  }

  if (choice == 3)
  {
    // Delete saved games
    Menu menu = create_or_switch_menu(DELETE_SLOT_MENU);
    menu.run();
    return;
  }
}

// Override this if pressing 0 does not exit the menu/program
void Menu::on_zero_option()
{
  if (menu_to_go_back_to)
    return exit_menu(menu_to_go_back_to);

  print("Exiting the program. Goodbye!\n");
  exit(0);
}

void Menu::exit_menu(Menu *destination_menu)
{
  // Switch to the destination menu
  // Do later
  return;
}

Menu create_or_switch_menu(string menu_type)
{
  // Check if the menu already exists
  if (!menu_list.empty())
  {
    for (auto &entry : menu_list)
    {
      Menu &menu = *entry;
      if (menu.title == menu_type)
      {
        return menu; // Return the existing menu
      }
    }
  }

  // Create menus if they don't exist
  if (menu_type == MAIN_MENU)
  {
    Menu *new_menu = new Menu();
    menu_list.push_back(new_menu);
    return *new_menu;
  }

  if (menu_type == LOAD_SLOT_MENU)
  {
    SaveSlotMenu *new_menu = new SaveSlotMenu(LOAD_SLOT_MENU);
    menu_list.push_back(new_menu);
    return *new_menu;
  }

  if (menu_type == SAVE_SLOT_MENU)
  {
    SaveSlotMenu *new_menu = new SaveSlotMenu(SAVE_SLOT_MENU);
    menu_list.push_back(new_menu);
    return *new_menu;
  }

  if (menu_type == DELETE_SLOT_MENU)
  {
    SaveSlotMenu *new_menu = new SaveSlotMenu(DELETE_SLOT_MENU);
    menu_list.push_back(new_menu);
    return *new_menu;
  }
}
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
