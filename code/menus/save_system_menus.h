#pragma once

#include <string>
#include <vector>
#include "base_menu.h"
#include "menu_system.h"
#include "code/save_system.h"
#include "code/defines.h"

using std::string;
using std::vector;

// Interface for managing saved game data; can be used for loading, saving, and deleting data
class SaveSlotMenu : public BaseMenu
{
private:
	string menu_type;

public:
	SaveSlotMenu(const string &type);

protected:
	Element create_header() override;

private:
	void populate_save_slots();
	void handle_load_selection(int slot_index);
	void handle_save_selection(int slot_index);
	void handle_delete_selection(int slot_index);
};

// Function declarations for the new menu system
int show_load_game_menu();
int show_save_game_menu();
int show_delete_saves_menu();
