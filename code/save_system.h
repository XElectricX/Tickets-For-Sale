#pragma once

#include <string>
#include <vector>
#include "game.h"

using std::string;
using std::vector;

extern vector<string> save_slot_index;

void update_save_slot_index();

void loadData(const string& filename, const string& slot_name);

void saveData(const Game& data, int slot_number, bool is_autosave = false);

void autosaveGameData(const Game& data);
