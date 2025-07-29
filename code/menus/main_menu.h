#pragma once

#include <vector>
#include <string>
#include "code/defines.h"

using std::string;
using std::vector;

class Menu
{
	public:
		string title = "Main Menu";

		//List of menu options; order of strings is the order they are displayed
		vector<string> options = {
			"Continue",
			"Load Saves",
			"Delete Saves"
		};
		//Every menu has an option for pressing 0; calls on_zero_option() when pressed
		string zero_option = "Exit";

		//Reference to the menu to go back to when this menu is exited; if empty, the program exits
		Menu* menu_to_go_back_to;

		void run();
		void display_choices();
		void pick_choice(int choice);
		void on_zero_option();
		void exit_menu(Menu* destination_menu);
};

Menu create_or_switch_menu(string menu_type = MAIN_MENU);

//Global list of existing menu objects
extern vector<Menu*> menu_list;
