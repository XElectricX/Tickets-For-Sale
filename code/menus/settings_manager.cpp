#include "settings_manager.h"
#include <iostream>
#include <fstream>
#include <algorithm>

// Initialize static variables with default values
int SettingsManager::master_volume = 80;
int SettingsManager::music_volume = 70;
int SettingsManager::effects_volume = 90;
bool SettingsManager::mute_audio = false;

bool SettingsManager::fullscreen_mode = false;
std::string SettingsManager::color_theme = "Default";
std::string SettingsManager::text_size = "Medium";
std::string SettingsManager::animation_speed = "Normal";

std::string SettingsManager::difficulty = "Normal";
bool SettingsManager::auto_save = true;
bool SettingsManager::show_hints = true;
bool SettingsManager::tutorial_mode = false;

// Sound settings methods
void SettingsManager::cycle_master_volume() {
    master_volume = (master_volume + 10) % 110;
    if (master_volume == 0) master_volume = 10; // Skip 0
}

void SettingsManager::cycle_music_volume() {
    music_volume = (music_volume + 10) % 110;
    if (music_volume == 0) music_volume = 10; // Skip 0
}

void SettingsManager::cycle_effects_volume() {
    effects_volume = (effects_volume + 10) % 110;
    if (effects_volume == 0) effects_volume = 10; // Skip 0
}

void SettingsManager::toggle_mute_audio() {
    mute_audio = !mute_audio;
}

// Display settings methods
void SettingsManager::toggle_fullscreen() {
    fullscreen_mode = !fullscreen_mode;
}

void SettingsManager::cycle_color_theme() {
    std::vector<std::string> themes = {"Default", "Dark", "Light", "Retro"};
    auto it = std::find(themes.begin(), themes.end(), color_theme);
    if (it != themes.end() && ++it != themes.end()) {
        color_theme = *it;
    } else {
        color_theme = themes[0];
    }
}

void SettingsManager::cycle_text_size() {
    std::vector<std::string> sizes = {"Small", "Medium", "Large"};
    auto it = std::find(sizes.begin(), sizes.end(), text_size);
    if (it != sizes.end() && ++it != sizes.end()) {
        text_size = *it;
    } else {
        text_size = sizes[0];
    }
}

void SettingsManager::cycle_animation_speed() {
    std::vector<std::string> speeds = {"Slow", "Normal", "Fast", "Off"};
    auto it = std::find(speeds.begin(), speeds.end(), animation_speed);
    if (it != speeds.end() && ++it != speeds.end()) {
        animation_speed = *it;
    } else {
        animation_speed = speeds[0];
    }
}

// Gameplay settings methods
void SettingsManager::cycle_difficulty() {
    std::vector<std::string> difficulties = {"Easy", "Normal", "Hard"};
    auto it = std::find(difficulties.begin(), difficulties.end(), difficulty);
    if (it != difficulties.end() && ++it != difficulties.end()) {
        difficulty = *it;
    } else {
        difficulty = difficulties[0];
    }
}

void SettingsManager::toggle_auto_save() {
    auto_save = !auto_save;
}

void SettingsManager::toggle_hints() {
    show_hints = !show_hints;
}

void SettingsManager::toggle_tutorial() {
    tutorial_mode = !tutorial_mode;
}

// Settings display methods
std::string SettingsManager::get_master_volume_text() {
    return "Master Volume: " + std::to_string(master_volume) + "%";
}

std::string SettingsManager::get_music_volume_text() {
    return "Music Volume: " + std::to_string(music_volume) + "%";
}

std::string SettingsManager::get_effects_volume_text() {
    return "Sound Effects: " + std::to_string(effects_volume) + "%";
}

std::string SettingsManager::get_mute_text() {
    return "Mute All Audio: " + std::string(mute_audio ? "On" : "Off");
}

std::string SettingsManager::get_fullscreen_text() {
    return "Fullscreen Mode: " + std::string(fullscreen_mode ? "On" : "Off");
}

std::string SettingsManager::get_color_theme_text() {
    return "Color Theme: " + color_theme;
}

std::string SettingsManager::get_text_size_text() {
    return "Text Size: " + text_size;
}

std::string SettingsManager::get_animation_speed_text() {
    return "Animation Speed: " + animation_speed;
}

std::string SettingsManager::get_difficulty_text() {
    return "Difficulty: " + difficulty;
}

std::string SettingsManager::get_auto_save_text() {
    return "Auto-Save: " + std::string(auto_save ? "Enabled" : "Disabled");
}

std::string SettingsManager::get_hints_text() {
    return "Hints: " + std::string(show_hints ? "Enabled" : "Disabled");
}

std::string SettingsManager::get_tutorial_text() {
    return "Tutorial Mode: " + std::string(tutorial_mode ? "On" : "Off");
}

void SettingsManager::reset_to_defaults() {
    // Reset to default values
    master_volume = 80;
    music_volume = 70;
    effects_volume = 90;
    mute_audio = false;

    fullscreen_mode = false;
    color_theme = "Default";
    text_size = "Medium";
    animation_speed = "Normal";

    difficulty = "Normal";
    auto_save = true;
    show_hints = true;
    tutorial_mode = false;
}

void SettingsManager::load_settings() {
    // Basic implementation - in a real game, this would load from a file
    // For demonstration purposes, we'll just use default values
    std::cout << "Loading settings..." << std::endl;
}

void SettingsManager::save_settings() {
    // Basic implementation - in a real game, this would save to a file
    std::cout << "Saving settings..." << std::endl;
}
