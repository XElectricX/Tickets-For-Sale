#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <tuple>

//Utility for advanced save slot ordering
// Returns a tuple: (is_autosave, slot_number, last_write_time, filename)
inline std::vector<std::tuple<bool, int, std::filesystem::file_time_type, std::string>>
get_all_save_slots(const std::string& save_folder, int max_save_slots, int max_autosave_slots) {
    using namespace std;
    using namespace std::filesystem;
    vector<tuple<bool, int, file_time_type, string>> slots;

    // Autosaves
    for (int i = 1; i <= max_autosave_slots; ++i) {
        string fname = save_folder + "/autosave" + to_string(i) + ".json";
        if (exists(fname)) {
            slots.emplace_back(true, i, last_write_time(fname), fname);
        }
    }
    // Manual saves
    for (int i = 1; i <= max_save_slots; ++i) {
        string fname = save_folder + "/slot" + to_string(i) + ".json";
        if (exists(fname)) {
            slots.emplace_back(false, i, last_write_time(fname), fname);
        } else {
            // Mark empty manual slots
            slots.emplace_back(false, i, file_time_type::min(), "");
        }
    }
    // Sort: autosaves (newest to oldest), then manual saves (slot 1 to N)
    sort(slots.begin(), slots.end(), [](const auto& a, const auto& b) {
        if (get<0>(a) != get<0>(b)) return get<0>(a) > get<0>(b); // autosave first
        if (get<0>(a)) return get<2>(a) > get<2>(b); // autosave: newest first
        return get<1>(a) < get<1>(b); // manual: slot number order
    });
    return slots;
}
