#pragma once
#include <map>
#include <string>

// Class to manage persistent menu state across navigation
class MenuStateManager {
private:
    static std::map<std::string, int> menu_selections;

public:
    // Get the last selected index for a menu
    static int get_selection(const std::string& menu_id) {
        if (menu_selections.find(menu_id) != menu_selections.end()) {
            return menu_selections[menu_id];
        }
        return 0; // Default to first option if no saved state
    }

    // Save the selected index for a menu
    static void save_selection(const std::string& menu_id, int selected_index) {
        menu_selections[menu_id] = selected_index;
    }
};
