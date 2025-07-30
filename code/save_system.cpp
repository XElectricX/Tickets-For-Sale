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
#include "game.h"
#include "objects/tickets.h"
#include "objects/customers.h"
#include "serialization.h"

using json = nlohmann::json;
using namespace std;

vector<string> save_slot_index;

//Loads Game data from a supplied JSON file
void loadData(const string& filename, const string& slot_name)
{
	ifstream file(filename);
	if(file.is_open())
	{
		json j;
		file >> j;
		// Each file is a single Game object, so just deserialize directly
		try {
			game_data = j.get<Game>();
		} catch (const std::exception& e) {
			cerr << "Failed to load game data: " << e.what() << "\n";
		}
		file.close();
	}
	else
	{
		cerr << "The file could not be loaded.\n";
	}
}


//Get a list of all existing save files and index them for easy access in save_slot_index
void update_save_slot_index()
{
	const string save_folder = "save data";

	save_slot_index.clear();

	//Check for both manual saves (slot[number].json) and autosaves (autosave[number].json)
	for(int i = 1; i <= MAX_SAVE_SLOTS; ++i)
	{
		//Check manual save
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
					cout << " | Total Tickets : " << value["ticket_data"] << "\n";
					cout << " | Economy: " << value["TICKET_CLASS_ECONOMY"] << "\n";
					cout << " | Business: " << value["TICKET_CLASS_BUSINESS"] << "\n";
					cout << " | First Class: " << value["TICKET_CLASS_LUXURY"] << "\n";
					cout << " | Total Currency: " << value["currency_amount"] << "\n\n";
				}
			}
		}

		//Check autosave
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


// Saves all fields of Game to a JSON file
void saveData(const Game& data, int slot_number, bool is_autosave)
{
	string save_folder = "save data";

	if(!filesystem::exists(save_folder))
	{
		filesystem::create_directory(save_folder);
	}

	//Naming convention: autosave1, autosave2, etc. for manual saves, while autosaves use autosave1, autosave2, etc.
	string filepath = save_folder + (is_autosave ? "/autosave" : "/slot") + to_string(slot_number) + ".json";

	//Prepare the JSON object for saving
	json j;
	// Save all fields in GameData
	j["money"] = game_data.money;
	j["player_name"] = game_data.player_name;
	j["business_name"] = game_data.business_name;
	j["money"] = game_data.money;
	j["ticket_inventory"] = game_data.ticket_inventory;
	j["tickets_for_sale"] = game_data.tickets_for_sale;
	j["customers"] = game_data.customers;
	j["total_customers"] = game_data.total_customers;
	j["total_tickets_sold"] = game_data.total_tickets_sold;
	j["total_tickets_bought"] = game_data.total_tickets_bought;
	j["total_revenue"] = game_data.total_revenue;
	j["total_expenses"] = game_data.total_expenses;

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

//Autosave function that saves the provided Game to the next autosave slot, rotating and overwriting the oldest if needed.
void autosaveGameData(const Game& data)
{
	update_save_slot_index();

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