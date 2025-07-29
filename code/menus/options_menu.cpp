#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/event.hpp>
#include <vector>
#include <string>
#include "menu_system.h"
#include "base_menu.h"
#include "settings_manager.h"

using namespace ftxui;

class OptionsMenu : public BaseMenu
{
public:
    OptionsMenu() : BaseMenu("⚙️ OPTIONS MENU ⚙️", "Configure Game Settings", "options_menu")
    {
        add_option("Sound Settings", 's', MENU_SOUND_SETTINGS);
        add_option("Display Settings", 'd', MENU_DISPLAY_SETTINGS);
        add_option("Gameplay Settings", 'g', MENU_GAMEPLAY_SETTINGS);
        add_option("Reset to Defaults", 'r', MENU_OPTIONS, [this]()
                   { reset_settings(); });
        add_option("Back to Main Menu", 'b', MENU_START_GAME); // Changed to go back to main menu

        set_footer("Use arrow keys, hotkeys [S/D/G/R/B], or Enter to select");
        set_theme_colors(Color::Magenta, Color::White, Color::Yellow, Color::Cyan);
    }

private:
    void reset_settings()
    {
        SettingsManager::reset_to_defaults();
    }

protected:
    Element create_header() override
    {
        return vbox({text("⚙️ OPTIONS MENU ⚙️") | bold | center | color(Color::Magenta),
                     text("Configure Game Settings") | center | color(Color::White),
                     separator(),
                     text("Customize your gaming experience") | dim | center});
    }
};

class SoundSettingsMenu : public BaseMenu
{
public:
    SoundSettingsMenu() : BaseMenu("🔊 SOUND SETTINGS", "Audio Configuration", "sound_settings_menu")
    {
        // Load dynamic menu options from the settings manager
        update_menu_options();

        set_footer("Use arrow keys, hotkeys [M/U/E/A/B], or Enter to adjust");
    }

private:
    void update_menu_options()
    {
        // Clear any existing options
        options.clear();

        // Add options with current setting values and actions to change them
        add_option(SettingsManager::get_master_volume_text(), 'm', MENU_SOUND_SETTINGS,
                   [this]()
                   {
                       SettingsManager::cycle_master_volume();
                       update_menu_options();
                   });

        add_option(SettingsManager::get_music_volume_text(), 'u', MENU_SOUND_SETTINGS,
                   [this]()
                   {
                       SettingsManager::cycle_music_volume();
                       update_menu_options();
                   });

        add_option(SettingsManager::get_effects_volume_text(), 'e', MENU_SOUND_SETTINGS,
                   [this]()
                   {
                       SettingsManager::cycle_effects_volume();
                       update_menu_options();
                   });

        add_option(SettingsManager::get_mute_text(), 'a', MENU_SOUND_SETTINGS,
                   [this]()
                   {
                       SettingsManager::toggle_mute_audio();
                       update_menu_options();
                   });

        add_option("Back to Options", 'b', MENU_OPTIONS); // Changed to go back to options menu
    }
};

class DisplaySettingsMenu : public BaseMenu
{
public:
    DisplaySettingsMenu() : BaseMenu("🖥️ DISPLAY SETTINGS", "Visual Configuration", "display_settings_menu")
    {
        // Load dynamic menu options from the settings manager
        update_menu_options();

        set_footer("Use arrow keys, hotkeys [F/C/T/A/B], or Enter to adjust");
    }

private:
    void update_menu_options()
    {
        // Clear any existing options
        options.clear();

        // Add options with current setting values and actions to change them
        add_option(SettingsManager::get_fullscreen_text(), 'f', MENU_DISPLAY_SETTINGS,
                   [this]()
                   {
                       SettingsManager::toggle_fullscreen();
                       update_menu_options();
                   });

        add_option(SettingsManager::get_color_theme_text(), 'c', MENU_DISPLAY_SETTINGS,
                   [this]()
                   {
                       SettingsManager::cycle_color_theme();
                       update_menu_options();
                   });

        add_option(SettingsManager::get_text_size_text(), 't', MENU_DISPLAY_SETTINGS,
                   [this]()
                   {
                       SettingsManager::cycle_text_size();
                       update_menu_options();
                   });

        add_option(SettingsManager::get_animation_speed_text(), 'a', MENU_DISPLAY_SETTINGS,
                   [this]()
                   {
                       SettingsManager::cycle_animation_speed();
                       update_menu_options();
                   });

        add_option("Back to Options", 'b', MENU_OPTIONS); // Changed to go back to options menu
    }
};

class GameplaySettingsMenu : public BaseMenu
{
public:
    GameplaySettingsMenu() : BaseMenu("🎮 GAMEPLAY SETTINGS", "Game Mechanics", "gameplay_settings_menu")
    {
        // Load dynamic menu options from the settings manager
        update_menu_options();

        set_footer("Use arrow keys, hotkeys [D/A/H/T/B], or Enter to adjust");
    }

private:
    void update_menu_options()
    {
        // Clear any existing options
        options.clear();

        // Add options with current setting values and actions to change them
        add_option(SettingsManager::get_difficulty_text(), 'd', MENU_GAMEPLAY_SETTINGS,
                   [this]()
                   {
                       SettingsManager::cycle_difficulty();
                       update_menu_options();
                   });

        add_option(SettingsManager::get_auto_save_text(), 'a', MENU_GAMEPLAY_SETTINGS,
                   [this]()
                   {
                       SettingsManager::toggle_auto_save();
                       update_menu_options();
                   });

        add_option(SettingsManager::get_hints_text(), 'h', MENU_GAMEPLAY_SETTINGS,
                   [this]()
                   {
                       SettingsManager::toggle_hints();
                       update_menu_options();
                   });

        add_option(SettingsManager::get_tutorial_text(), 't', MENU_GAMEPLAY_SETTINGS,
                   [this]()
                   {
                       SettingsManager::toggle_tutorial();
                       update_menu_options();
                   });

        add_option("Back to Options", 'b', MENU_OPTIONS); // Changed to go back to options menu
    }
};

int show_options_menu()
{
    OptionsMenu menu;
    int result = menu.show();

    // Handle sub-menu navigation
    while (result == MENU_SOUND_SETTINGS || result == MENU_DISPLAY_SETTINGS || result == MENU_GAMEPLAY_SETTINGS)
    {
        switch (result)
        {
        case MENU_SOUND_SETTINGS:
        {
            SoundSettingsMenu sound_menu;
            result = sound_menu.show();
            if (result == MENU_OPTIONS)
            {
                result = show_options_menu(); // Return to options menu
            }
            break;
        }
        case MENU_DISPLAY_SETTINGS:
        {
            DisplaySettingsMenu display_menu;
            result = display_menu.show();
            if (result == MENU_OPTIONS)
            {
                result = show_options_menu(); // Return to options menu
            }
            break;
        }
        case MENU_GAMEPLAY_SETTINGS:
        {
            GameplaySettingsMenu gameplay_menu;
            result = gameplay_menu.show();
            if (result == MENU_OPTIONS)
            {
                result = show_options_menu(); // Return to options menu
            }
            break;
        }
        }
    }

    return result;
}