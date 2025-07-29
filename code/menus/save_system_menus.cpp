#include <iostream>
#include <string>
#include "code/save_system.h"
#include "code/helpers.h"
#include "code/menus/save_system_menus.h"
#include "code/defines.h"

using std::string;
using std::to_string;

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
	update_save_slot_index();

	// Add save slots as options
	for (size_t i = 0; i < save_slot_index.size() && i < MAX_SAVE_SLOTS; ++i)
	{
		string slot_text = "Slot " + to_string(i + 1) + ": ";
		if (save_slot_index[i].empty() || save_slot_index[i] == "Empty")
		{
			slot_text += "[Empty]";
		}
		else
		{
			slot_text += save_slot_index[i];
		}

		char hotkey = '1' + static_cast<char>(i);
		int return_value = 100 + static_cast<int>(i); // Use 100+ for slot indices

		if (menu_type == LOAD_SLOT_MENU)
		{
			add_option(slot_text, hotkey, return_value, [this, i]()
					   { handle_load_selection(static_cast<int>(i)); });
		}
		else if (menu_type == SAVE_SLOT_MENU)
		{
			add_option(slot_text, hotkey, return_value, [this, i]()
					   { handle_save_selection(static_cast<int>(i)); });
		}
		else if (menu_type == DELETE_SLOT_MENU)
		{
			add_option(slot_text, hotkey, return_value, [this, i]()
					   { handle_delete_selection(static_cast<int>(i)); });
		}
	}

	// Add back option
	add_option("Back to Main Menu", 'b', MENU_START_GAME);
}

void SaveSlotMenu::handle_load_selection(int slot_index)
{
	if (slot_index < 0 || slot_index >= static_cast<int>(save_slot_index.size()))
	{
		return;
	}

	if (save_slot_index[slot_index].empty() || save_slot_index[slot_index] == "Empty")
	{
		// Could add error handling here - for now just return
		return;
	}

	// TODO: Implement actual loading logic
	// GameData data;
	// data.loadData("save_data.json", save_slot_index[slot_index]);

	// For now, just show a placeholder message
	std::cout << "Loading from slot " << (slot_index + 1) << ": " << save_slot_index[slot_index] << std::endl;
}

void SaveSlotMenu::handle_save_selection(int slot_index)
{
	if (slot_index < 0 || slot_index >= MAX_SAVE_SLOTS)
	{
		return;
	}

	// TODO: Implement actual saving logic
	// GameData current_data;
	// current_data = current_data.read_current_game_state("current_game.json");
	// saveData(current_data, slot_index + 1);

	// For now, just show a placeholder message
	std::cout << "Saving to slot " << (slot_index + 1) << std::endl;

	// Refresh the options to show the updated save
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
	return menu.show();
}

int show_save_game_menu()
{
	SaveSlotMenu menu(SAVE_SLOT_MENU);
	return menu.show();
}

int show_delete_saves_menu()
{
	SaveSlotMenu menu(DELETE_SLOT_MENU);
	return menu.show();
}
