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
		void pick_choice(int choice) override;

		void populate_options();

		SaveSlotMenu(string title = LOAD_SLOT_MENU);
};
