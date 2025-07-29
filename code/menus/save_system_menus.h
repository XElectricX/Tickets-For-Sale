#pragma once

#include <string>
#include <vector>
#include "code/menus/main_menu.h"
#include "code/save_system.h"
#include "code/defines.h"

//Interface for managing saved game data; can be used for loading, saving, and deleting data
class SaveSlotMenu : public Menu
{
	public:
		string title = LOAD_SLOT_MENU;

		//Saved games are displayed as options programmatically
		vector<string> options = {};
		//Every menu has an option for pressing 0; calls on_zero_option() when pressed
		string zero_option = "Exit";

		//Reference to the menu to go back to when this menu is exited; if empty, the program exits
		Menu* menu_to_go_back_to;

		void run();
		void display_choices();
		void pick_choice(int choice);
		void on_zero_option();
		void exit_menu(Menu* destination_menu);

		void populate_options();

		SaveSlotMenu(string title = LOAD_SLOT_MENU);
};
