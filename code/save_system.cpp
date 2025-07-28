#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

// Structure for game data
struct GameData {
    string current_day;
    string ticket_data;
    string TICKET_CLASS_ECONOMY, TICKET_CLASS_BUSINESS, TICKET_CLASS_LUXURY;
    string currency_amount;
};

const vector<string > allowed_slots = { "slot1", "slot2", "slot3", "slot4", "slot5" };

void writeExampleAutoSave(const string& filename) {
    GameData example_data = {
        "3", // game_date
        "60", // ticket_data (Total Tickets)
        "30", // TICKET_CLASS_ECONOMY
        "20", // TICKET_CLASS_BUSINESS
        "10", // TICKET_CLASS_LUXURY
        "500", // currency_amount

    };

    json j;
    j["current_day"] = example_data.current_day;
    j["ticket_data"] = example_data.ticket_data;
    j["TICKET_CLASS_ECONOMY"] = example_data.TICKET_CLASS_ECONOMY;
    j["TICKET_CLASS_BUSINESS"] = example_data.TICKET_CLASS_BUSINESS;
    j["TICKET_CLASS_LUXURY"] = example_data.TICKET_CLASS_LUXURY;
    j["currency_amount"] = example_data.currency_amount;



    ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
        cout << "Example auto-save data written to '" << filename << "'.\n";
    }
    else {
        cerr << "Failed to save to '" << filename << "'.\n";
    }
}

GameData read_current_game_state(const string& filename) {
    GameData data;
	ifstream file(filename);
    if (file.is_open()) {
        json j;
        file >> j;
        file.close();

        if (j.contains("current_day")) data.current_day = j["current_day"];
        if (j.contains("ticket_data")) data.ticket_data = j["ticket_data"];
        if (j.contains("TICKET_CLASS_ECONOMY")) data.TICKET_CLASS_ECONOMY = j["TICKET_CLASS_ECONOMY"];
        if (j.contains("TICKET_CLASS_BUSINESS")) data.TICKET_CLASS_BUSINESS = j["TICKET_CLASS_BUSINESS"];
        if (j.contains("TICKET_CLASS_LUXURY")) data.TICKET_CLASS_LUXURY = j["TICKET_CLASS_LUXURY"];
        if (j.contains("currency_amount")) data.currency_amount = j["currency_amount"];

        cout << "\n--- Loaded from autosave ---\n";
		cout << "Day: " << data.current_day << "\n";
		cout << "Total Tickets: " << data.ticket_data << "\n";
		cout << "-Economy Class: " << data.TICKET_CLASS_ECONOMY << "\n";
		cout << "-Business Class: " << data.TICKET_CLASS_BUSINESS << "\n";
		cout << "-First Class: " << data.TICKET_CLASS_LUXURY << "\n";
		cout << "Total Currency: " << data.currency_amount << "\n";
		cout << "-----------------------------\n";
    }
    else {
        cerr << "Could not open file: " << filename << "\n";
    }
	return data;
}

// Save data to JSON file
void saveData(const GameData& data, const string& filename, const string& slot_name) {
    json j;
    ifstream inFile(filename);
    if (inFile.is_open()) {
        try {
            if (inFile.peek() != ifstream::traits_type::eof()) {
                inFile >> j;
            }
        }
        catch (const std::exception& e) {
            j = json::object();
        }
        inFile.close();
    }

    // Checking for slot limit
    if (!j.contains(slot_name) && j.size() >= 5) {
        cout << "Maximum save slots reached. Please delete an existing slot before saving.\n";
        return;
    }

    // Prompt for overwrite only if the slot already exists
    if (j.contains(slot_name)) {
        char confirm;
        cout << "Slot '" << slot_name << "' already has a save. Do you want to overwrite it? (y/n): ";
        cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') {
            cout << "Save cancelled.\n";
            return;
        }
    }

    j[slot_name]["current_day"] = data.current_day;
    j[slot_name]["ticket_data"] = data.ticket_data;
    j[slot_name]["TICKET_CLASS_ECONOMY"] = data.TICKET_CLASS_ECONOMY;
	j[slot_name]["TICKET_CLASS_BUSINESS"] = data.TICKET_CLASS_BUSINESS;
	j[slot_name]["TICKET_CLASS_LUXURY"] = data.TICKET_CLASS_LUXURY;
    j[slot_name]["currency_amount"] = data.currency_amount;

    ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
        cout << "Data saved to slot: "<< slot_name << "\n";
    }
    else {
        cout << "File could not be saved.\n";
    }
}

// Load data from JSON file
GameData loadData(const string& filename, const string& slot_name) {
    GameData data;
    ifstream file(filename);
    if (file.is_open()) {
        json j;
        file >> j;

        if (j.contains(slot_name)) {
            auto slot = j[slot_name];
            data.current_day = slot["current_day"];
            data.ticket_data = slot["ticket_data"];
            data.TICKET_CLASS_ECONOMY = slot["TICKET_CLASS_ECONOMY"];
            data.TICKET_CLASS_BUSINESS = slot["TICKET_CLASS_BUSINESS"];
            data.TICKET_CLASS_LUXURY = slot["TICKET_CLASS_LUXURY"];
            data.currency_amount = slot["currency_amount"];
            cout << "Data loaded from slot: " << slot_name << "\n";
        }
        else {
            cerr << "Slot " << slot_name << " not found.\n";
        }

        file.close();
    }
    else {
        cerr << "The file could not be loaded.\n";
    }
    return data;
}

void listSaveSlots(const string& filename) {
    ifstream file(filename);
    json j;
    if (file.is_open()) {
        if (file.peek() != ifstream::traits_type::eof()) {
            file >> j;
        }
        file.close();
    }
        cout << "\n--- Save Slots ---\n";
        for (const auto& slot : allowed_slots) {
            if (j.contains(slot)) {
                auto& value = j[slot];
                cout << "Slot: " << slot << "(USED)\n";
                if (value.is_object()) {
                    cout << " | Day " << value["current_day"] << "\n";
                    cout << " | Total Tickets : " << value["ticket_data"] << "\n";
                    cout << " | Economy: " << value["TICKET_CLASS_ECONOMY"] << "\n";
                    cout << " | Business: " << value["TICKET_CLASS_BUSINESS"] << "\n";
                    cout << " | First Class: " << value["TICKET_CLASS_LUXURY"] << "\n";
                    cout << " | Total Currency: " << value["currency_amount"] << "\n\n";
                }
                else {
                    cout << "Slot: " << slot << " (EMPTY)\n";
                }
            }
        }
}

bool isValidSlot(const string& slot) {
    return find(allowed_slots.begin(), allowed_slots.end(), slot) != allowed_slots.end();
}

// Menu
void menu() {
    GameData data;
    string filename = "TrainFile.json";
    string autosave_file = "AutoSave.json";
    int choice;
    string slot;

    while (true) {  // add multiple save slots to the save menu
        cout << "\n--- Menu ---\n";
        cout << "1. Save Game\n";
        cout << "2. Load Game\n";
		cout << "3. List Save Slots\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
			listSaveSlots(filename);
            cout << "Enter save slot name (slot1-slot5): ";
            cin >> slot;
            if (!isValidSlot(slot)) {
				cout << "Invalid slot. Please enter a slot name between slot1 and slot5.\n";
                continue;
            }

			data = read_current_game_state(autosave_file);
            saveData(data, filename, slot);
        }
        else if (choice == 2) {
            listSaveSlots(filename);
            cout << "Enter the save slot name to load: ";
            cin >> slot;
            if (!isValidSlot(slot)) {
                cout << "Invalid slot. \n";
                continue;
            }

            data = loadData(filename, slot);
            cout << "Day " << data.current_day << "\n";
            cout << "Total Tickets: " << data.ticket_data << "\n";
            cout << "Ticket amount for: \n";
            cout << " - Economy Class: "<< data.TICKET_CLASS_ECONOMY << "\n";
            cout << " - Business Class: " << data.TICKET_CLASS_BUSINESS << "\n";
            cout << " - First Class: " << data.TICKET_CLASS_LUXURY << "\n";
            cout << "Total Currency: " << data.currency_amount << "\n";
        }
        else if (choice == 3) {
            listSaveSlots(filename);
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }
}

int main() {
	writeExampleAutoSave("AutoSave.json");
    menu();
    return 0;
}