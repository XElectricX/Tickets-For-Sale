#pragma once
#include <string>
#include <vector>
#include <map>

// Manages and persists game settings across sessions
class SettingsManager {
public:
    // Sound settings
    static int master_volume;       // 0-100
    static int music_volume;        // 0-100
    static int effects_volume;      // 0-100
    static bool mute_audio;         // true = muted

    // Display settings
    static bool fullscreen_mode;    // true = fullscreen
    static std::string color_theme; // "Default", "Dark", "Light", "Retro"
    static std::string text_size;   // "Small", "Medium", "Large"
    static std::string animation_speed; // "Slow", "Normal", "Fast", "Off"

    // Gameplay settings
    static std::string difficulty;  // "Easy", "Normal", "Hard"
    static bool auto_save;          // true = enabled
    static bool show_hints;         // true = enabled
    static bool tutorial_mode;      // true = enabled

    // Settings cycling methods
    static void cycle_master_volume();
    static void cycle_music_volume();
    static void cycle_effects_volume();
    static void toggle_mute_audio();
    static void toggle_fullscreen();
    static void cycle_color_theme();
    static void cycle_text_size();
    static void cycle_animation_speed();
    static void cycle_difficulty();
    static void toggle_auto_save();
    static void toggle_hints();
    static void toggle_tutorial();

    // Settings display methods
    static std::string get_master_volume_text();
    static std::string get_music_volume_text();
    static std::string get_effects_volume_text();
    static std::string get_mute_text();
    static std::string get_fullscreen_text();
    static std::string get_color_theme_text();
    static std::string get_text_size_text();
    static std::string get_animation_speed_text();
    static std::string get_difficulty_text();
    static std::string get_auto_save_text();
    static std::string get_hints_text();
    static std::string get_tutorial_text();

    // Load and save settings
    static void reset_to_defaults();
    static void load_settings(); // Load from file (if exists)
    static void save_settings(); // Save to file
};
