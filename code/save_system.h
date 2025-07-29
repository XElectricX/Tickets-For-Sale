#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

// Structure for game data
struct GameData
{
	public:
		string current_day;
		string ticket_data;
		string TICKET_CLASS_ECONOMY, TICKET_CLASS_BUSINESS, TICKET_CLASS_LUXURY;
		string currency_amount;

		GameData read_current_game_state(const string& filename);
		GameData loadData(const string& filename, const string& slot_name);
};

extern vector<string> save_slot_index;

void update_save_slot_index();

void saveData(const GameData& data, int slot_number, bool is_autosave = false);

void autosaveGameData(const GameData& data);
