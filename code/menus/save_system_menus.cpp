#include <iostream>
#include <string>
#include "code/save_system.h"
#include "code/helpers.h"
#include "code/menus/main_menu.h"
#include "code/menus/save_system_menus.h"
#include "code/defines.h"

using std::string;
using std::to_string;

SaveSlotMenu::SaveSlotMenu(string title)
{
	this->title = title;
	populate_options();
};

void SaveSlotMenu::pick_choice(int choice)
{
	//Can't use switch() with a string because C++ is obtuse
	if(title == LOAD_SLOT_MENU)
	{
		// Handle load logic
		return;
	}

	if(title == SAVE_SLOT_MENU)
	{
		// Handle save logic
		return;
	}

	if(title == DELETE_SLOT_MENU)
	{
		// Handle delete logic
		return;
	}
}

void SaveSlotMenu::populate_options()
{
	options.clear();
	update_save_slot_index();
	options = save_slot_index;
}
