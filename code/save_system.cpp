#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include "save_system.h"
#include <nlohmann/json.hpp>
#include "helpers.h"
#include "defines.h"

using json = nlohmann::json;
using namespace std;


vector<string> save_slot_index;

// Copilot: Reads the current game state from a JSON file (autosave) and prints the loaded values.
GameData GameData::read_current_game_state(const string& filename)
{
	GameData data;
	ifstream file(filename);
	if(file.is_open())
	{
		json j;
		file >> j;
		file.close();

		// Copilot: Extract each field from the JSON if it exists
		if(j.contains("current_day"))
			data.current_day = j["current_day"];
		if(j.contains("ticket_data"))
			data.ticket_data = j["ticket_data"];
		if(j.contains("TICKET_CLASS_ECONOMY"))
			data.TICKET_CLASS_ECONOMY = j["TICKET_CLASS_ECONOMY"];
		if(j.contains("TICKET_CLASS_BUSINESS"))
			data.TICKET_CLASS_BUSINESS = j["TICKET_CLASS_BUSINESS"];
		if(j.contains("TICKET_CLASS_LUXURY"))
			data.TICKET_CLASS_LUXURY = j["TICKET_CLASS_LUXURY"];
		if(j.contains("currency_amount"))
			data.currency_amount = j["currency_amount"];

		// Copilot: Print out the loaded data for debugging/confirmation
		cout << "\n--- Loaded from autosave ---\n";
		cout << "Day: " << data.current_day << "\n";
		cout << "Total Tickets: " << data.ticket_data << "\n";
		cout << "-Economy Class: " << data.TICKET_CLASS_ECONOMY << "\n";
		cout << "-Business Class: " << data.TICKET_CLASS_BUSINESS << "\n";
		cout << "-First Class: " << data.TICKET_CLASS_LUXURY << "\n";
		cout << "Total Currency: " << data.currency_amount << "\n";
		cout << "-----------------------------\n";
	}
	else
		cerr << "Could not open file: " << filename << "\n";

	// Copilot: Return the loaded game data (or default if file not found)
	return data;
}

// Copilot: Loads GameData from a specific slot in the JSON file.
// Copilot: Reads the file, finds the slot, and populates the GameData struct.
GameData GameData::loadData(const string& filename, const string& slot_name)
{
	GameData data;
	ifstream file(filename);
	if(file.is_open())
	{
		json j;
		file >> j;

		// Copilot: Check if the requested slot exists
		if(j.contains(slot_name))
		{
			auto slot = j[slot_name];
			data.current_day = slot["current_day"];
			data.ticket_data = slot["ticket_data"];
			data.TICKET_CLASS_ECONOMY = slot["TICKET_CLASS_ECONOMY"];
			data.TICKET_CLASS_BUSINESS = slot["TICKET_CLASS_BUSINESS"];
			data.TICKET_CLASS_LUXURY = slot["TICKET_CLASS_LUXURY"];
			data.currency_amount = slot["currency_amount"];
			cout << "Data loaded from slot: " << slot_name << "\n";
		}
		else
			cerr << "Slot " << slot_name << " not found.\n";

		file.close();
	}
	else
		cerr << "The file could not be loaded.\n";

	// Copilot: Return the loaded data (or default if not found)
	return data;
}


//Get a list of all existing save files and index them for easy access in save_slot_index
void update_save_slot_index()
{
	const string save_folder = "save data";

	save_slot_index.clear();

	// Copilot: Check for both manual saves (slot[number].json) and autosaves (autosave[number].json)
	for(int i = 1; i <= MAX_SAVE_SLOTS; ++i)
	{
		// Copilot: Check manual save
		string manual_filepath = save_folder + "/slot" + to_string(i) + ".json";
		if(filesystem::exists(manual_filepath))
		{
			save_slot_index.push_back(manual_filepath);

			ifstream file(manual_filepath);
			if(file.is_open())
			{
				json value;
				file >> value;
				print("Slot: " + to_string(i) + " (USED)\n");
				if(value.is_object())
				{
					cout << " | Day " << value["current_day"] << "\n";
					cout << " | Total Tickets : " << value["ticket_data"] << "\n";
					cout << " | Economy: " << value["TICKET_CLASS_ECONOMY"] << "\n";
					cout << " | Business: " << value["TICKET_CLASS_BUSINESS"] << "\n";
					cout << " | First Class: " << value["TICKET_CLASS_LUXURY"] << "\n";
					cout << " | Total Currency: " << value["currency_amount"] << "\n\n";
				}
			}
		}

		// Copilot: Check autosave
		string autosave_filepath = save_folder + "/autosave" + to_string(i) + ".json";
		if(filesystem::exists(autosave_filepath))
		{
			save_slot_index.push_back(autosave_filepath);

			ifstream file(autosave_filepath);
			if(file.is_open())
			{
				json value;
				file >> value;
				print("Autosave: " + to_string(i) + " (USED)\n");
				if(value.is_object())
				{
					cout << " | Day " << value["current_day"] << "\n";
					cout << " | Total Tickets : " << value["ticket_data"] << "\n";
					cout << " | Economy: " << value["TICKET_CLASS_ECONOMY"] << "\n";
					cout << " | Business: " << value["TICKET_CLASS_BUSINESS"] << "\n";
					cout << " | First Class: " << value["TICKET_CLASS_LUXURY"] << "\n";
					cout << " | Total Currency: " << value["currency_amount"] << "\n\n";
				}
			}
		}
	}

	if(save_slot_index.empty())
		return;

	//Sort the save_slot_index vector alphabetically
	std::sort(save_slot_index.begin(), save_slot_index.end());
}

// Copilot: Saves the provided GameData to an individual file for each slot in the 'save data' directory.
// Copilot: The file is named 'slot[slot_number].json' and stored in 'save data/'.
// Copilot: Prompts the user if overwriting an existing slot file, except for autosaves.
void saveData(const GameData& data, int slot_number, bool is_autosave)
{
	// Copilot: Build the file path for the slot
	string save_folder = "save data";

	// Copilot: Ensure the save directory exists (C++17 and later)
	if(!filesystem::exists(save_folder))
	{
		filesystem::create_directory(save_folder);
	}

	//Naming convention: autosave1, autosave2, etc. for manual saves, while autosaves use autosave1, autosave2, etc.
	string filepath = save_folder + (is_autosave ? "/autosave" : "/slot") + to_string(slot_number) + ".json";

	// Copilot: For manual saves, prompt if overwriting. For autosaves, always overwrite.
	if(!is_autosave && filesystem::exists(filepath))
	{
		char confirm;

		cout << "Slot '" << slot_number << "' already has a save. Do you want to overwrite it? (y/n): ";
		cin >> confirm;

		if(confirm != 'y' && confirm != 'Y')
		{
			print("Save cancelled.\n");
			return;
		}
	}

	// Copilot: Prepare the JSON object for saving
	json j;

	j["current_day"] = data.current_day;
	j["ticket_data"] = data.ticket_data;
	j["TICKET_CLASS_ECONOMY"] = data.TICKET_CLASS_ECONOMY;
	j["TICKET_CLASS_BUSINESS"] = data.TICKET_CLASS_BUSINESS;
	j["TICKET_CLASS_LUXURY"] = data.TICKET_CLASS_LUXURY;
	j["currency_amount"] = data.currency_amount;

	// Copilot: Write the JSON data to the slot file
	ofstream file(filepath);

	if(file.is_open())
	{
		file << j.dump(4);
		file.close();

		print("Data saved to slot: " + to_string(slot_number) + "\n");
	}

	else
		print("File could not be saved.\n");
}

// Copilot: Autosave function that saves the provided GameData to the next autosave slot, rotating and overwriting the oldest if needed.
void autosaveGameData(const GameData& data)
{
	if(save_slot_index.empty())
	{
		//There don't appear to be any save slots, so just use the first autosave slot
		return saveData(data, 1, true);
	}

	//Keep a tally of the number of autosaves
	int autosave_count = 0;
	string oldest_autosave = save_slot_index.front();
	//Loop through to see which of the "autosave[number].json" files is oldest
	for(const auto& slot : save_slot_index)
	{
		if(slot.find("autosave") != string::npos)
		{
			autosave_count++;

			//Set the current autosave as the oldest one if it is older than the current oldest
			if(filesystem::last_write_time(slot) < filesystem::last_write_time(oldest_autosave))
				oldest_autosave = slot;
		}
	}

	if(autosave_count < MAX_AUTO_SAVE_SLOTS)
	{
		//There are less than the maximum number of autosaves, so just save to the next slot
		return saveData(data, autosave_count + 1, true);
	}

	//Overwrite the oldest autosave
	int slot_number = stoi(oldest_autosave.substr(oldest_autosave.find("autosave") + 8, 1));
	saveData(data, slot_number, true);
}
