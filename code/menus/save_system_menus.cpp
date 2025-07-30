#include <iostream>
#include <string>
#include "code/save_system.h"
#include "code/helpers.h"
#include "code/menus/save_system_menus.h"
#include "code/menus/save_slot_utils.h"
#include "code/defines.h"
#include "code/game.h"

using std::string;
using std::to_string;
using std::get;

SaveSlotMenu::SaveSlotMenu(const string &type)
	: BaseMenu("", "", "save_slot_menu"), menu_type(type)
{
	if (type == LOAD_SLOT_MENU)
	{
		title = "🔄 Load Game";
		subtitle = "Select a save slot to load";
	}
	else if (type == SAVE_SLOT_MENU)
	{
		title = "💾 Save Game";
		subtitle = "Select a slot to save your progress";
	}
	else if (type == DELETE_SLOT_MENU)
	{
		title = "🗑️ Delete Saves";
		subtitle = "Select a save slot to delete";
	}

	populate_save_slots();
	set_footer("Use arrow keys or Enter to select • ESC to go back");
	set_theme_colors(Color::Cyan, Color::White, Color::Yellow, Color::Green);
}

Element SaveSlotMenu::create_header()
{
	string icon = "💾";
	if (menu_type == LOAD_SLOT_MENU)
		icon = "🔄";
	else if (menu_type == DELETE_SLOT_MENU)
		icon = "🗑️";

	return vbox({text(title) | bold | center | color(Color::Cyan),
				 text(subtitle) | center | color(Color::White),
				 separator(),
				 text("Available save slots:") | dim | center});
}

void SaveSlotMenu::populate_save_slots()
{

	string save_folder = "save data";
	auto slots = get_all_save_slots(save_folder, MAX_SAVE_SLOTS, MAX_AUTO_SAVE_SLOTS);
	int display_idx = 0;
	for (const auto& slot : slots) {
		bool is_autosave = get<0>(slot);
		int slot_num = get<1>(slot);
		auto mod_time = get<2>(slot);
		const string& fname = get<3>(slot);
		string slot_text;
		if (menu_type == SAVE_SLOT_MENU && is_autosave) {
			continue; // Do not show autosave slots in save menu
		}
		if (is_autosave) {
			if (!fname.empty()) {
				slot_text = "AUTOSAVE " + to_string(slot_num) + " (" + fname + ")";
			} else {
				continue;
			}
		} else {
			slot_text = "SLOT " + to_string(slot_num) + ": ";
			if (fname.empty()) {
				slot_text += "EMPTY";
			} else {
				slot_text += fname;
			}
		}
		char hotkey = '1' + (display_idx % 9);
		int return_value = 100 + display_idx;
		if (menu_type == LOAD_SLOT_MENU) {
			add_option(slot_text, hotkey, return_value, [this, display_idx]() { handle_load_selection(display_idx); });
		} else if (menu_type == SAVE_SLOT_MENU) {
			add_option(slot_text, hotkey, return_value, [this, display_idx]() { handle_save_selection(display_idx); });
		} else if (menu_type == DELETE_SLOT_MENU) {
			add_option(slot_text, hotkey, return_value, [this, display_idx]() { handle_delete_selection(display_idx); });
		}
		++display_idx;
	}

	add_option("Back to Main Menu", 'b', MENU_START_GAME);
}

void SaveSlotMenu::handle_load_selection(int slot_index)
{
	// Instead of using slot_index directly, search for the Nth non-empty slot
	if (slot_index < 0)
	{
		return;
	}

	std::string filepath = "";
	for (const auto& fname : save_slot_index)
	{
		if (!fname.empty() && fname != "Empty")
		{
			//Check the number after "slot" in the filename
			std::string file = fname.substr(fname.find_last_of("/\\") + 1);
			size_t found = file.find("slot");
			if(found == std::string::npos)
			{
				continue; // Not a valid save slot filename
			}

			filepath = fname;
			}
		}

	if (filepath.empty())
	{
		// No valid file found for this slot index
		return;
	}

	// The slot name is the filename without the path and extension
	std::string slot_name = filepath.substr(filepath.find_last_of("/\\") + 1);
	size_t dot = slot_name.find_last_of('.');
	if (dot != std::string::npos) {
		slot_name = slot_name.substr(0, dot);
	}
	loadData(filepath, slot_name);
}

void SaveSlotMenu::handle_save_selection(int slot_index)
{
	if (slot_index < 0 || slot_index >= MAX_SAVE_SLOTS)
	{
		return;
	}

	//Implement actual saving logic using saveData and game_data
	// Only manual slots are shown, so slot_index maps to slot number (1-based)
	int slot_number = slot_index + 1;
	saveData(game_data, slot_number, false);
	populate_save_slots();
}

void SaveSlotMenu::handle_delete_selection(int slot_index)
{
	if (slot_index < 0 || slot_index >= static_cast<int>(save_slot_index.size()))
	{
		return;
	}

	if (save_slot_index[slot_index].empty() || save_slot_index[slot_index] == "Empty")
	{
		// Nothing to delete
		return;
	}

	// TODO: Implement actual deletion logic
	// This would involve removing the save file and updating the index

	// For now, just show a placeholder message
	std::cout << "Deleting slot " << (slot_index + 1) << ": " << save_slot_index[slot_index] << std::endl;

	// Refresh the options to show the updated saves
	populate_save_slots();
}

// Function implementations for the new menu system
int show_load_game_menu()
{
	SaveSlotMenu menu(LOAD_SLOT_MENU);
	int result = menu.show();
	//If a slot was selected, load in to the ticket counter menu
	return result >= 100 ? MENU_TICKET_COUNTER : result;
}

int show_save_game_menu()
{
	SaveSlotMenu menu(SAVE_SLOT_MENU);
	int result = menu.show();
	//If a slot was selected, always return MENU_BACK to go to previous menu
	return result >= 100 ? MENU_BACK : result;
}

int show_delete_saves_menu()
{
	SaveSlotMenu menu(DELETE_SLOT_MENU);
	int result = menu.show();
	return result >= 100 ? MENU_BACK : result;
}
