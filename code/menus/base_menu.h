#pragma once
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/event.hpp>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include "menu_system.h"
#include "menu_state_manager.h"

using namespace ftxui;

struct GameMenuOption {  // Renamed from MenuOption to avoid conflict with ftxui::MenuOption
    std::string text;
    char hotkey;
    int return_value;
    std::function<void()> action = nullptr; // Optional action to perform
};

class BaseMenu {
protected:
    std::string title;
    std::string subtitle;
    std::vector<GameMenuOption> options;  // Updated to use GameMenuOption
    std::vector<std::string> status_info;
    std::string footer_text;
    std::string menu_id;  // Unique identifier for this menu for state persistence
    bool persist_selection = true;  // Whether to persist the selection state

    // Theme colors
    Color title_color = Color::White;
    Color subtitle_color = Color::GrayLight;
    Color hotkey_color = Color::Yellow;
    Color status_color = Color::Cyan;

public:
    BaseMenu(const std::string& title, const std::string& subtitle = "", const std::string& menu_id = "");
    virtual ~BaseMenu() = default;

    // Configuration methods
    void add_option(const std::string& text, char hotkey, int return_value, std::function<void()> action = nullptr);
    void add_status_info(const std::string& info);
    void set_footer(const std::string& text);
    void set_theme_colors(Color title, Color subtitle, Color hotkey, Color status);
    void set_menu_id(const std::string& id) { menu_id = id; }
    void set_persist_selection(bool persist) { persist_selection = persist; }

    // Main menu display method
    virtual int show();

protected:
    // Virtual methods for customization
    virtual Element create_header();
    virtual Element create_menu_content();
    virtual Element create_status_bar();
    virtual Element create_footer();
    virtual bool handle_custom_events(Event event);

private:
    Component create_menu_component();
    Element format_option_text(const GameMenuOption& option, bool is_selected);  // Updated parameter type
};
