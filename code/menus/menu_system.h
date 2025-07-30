#pragma once
#include <string>

// Forward declaration of BaseMenu
class BaseMenu;

// Menu function declarations
int show_main_menu();
int show_ticket_counter_menu();
int show_ticket_inventory_menu();
int show_ticket_purchasing_menu();
int show_barter_menu();
int show_options_menu();
int show_statistics_menu();

// Save system menu functions
int show_load_game_menu();
int show_save_game_menu();
int show_delete_saves_menu();

// Enhanced menu return codes with better organization
enum MenuResult
{
    // Core navigation
    MENU_EXIT = 0,
    MENU_BACK = 1,

    // Main flow
    MENU_START_GAME = 10,
    MENU_LOAD_GAME = 11,
    MENU_SAVE_GAME = 12,
    MENU_OPTIONS = 13,

    // Game menus
    MENU_TICKET_COUNTER = 20,
    MENU_INVENTORY = 21,
    MENU_PURCHASE = 22,
    MENU_BARTER = 23,
    MENU_STATISTICS = 24,

    // Sub-menus for options
    MENU_SOUND_SETTINGS = 30,
    MENU_DISPLAY_SETTINGS = 31,
    MENU_GAMEPLAY_SETTINGS = 32,

    // Error states
    MENU_ERROR = -1
};

// Game state interface for menus
struct GameState
{
    int cash = 1250;
    int tickets_in_stock = 47;
    int tickets_sold_today = 12;
    int daily_revenue = 347;

    // Statistics
    int total_tickets_sold = 152;
    int total_tickets_bought = 199;
    int total_revenue = 15250;
    int total_expenses = 9950;
    float average_markup = 27.5f;
    std::string most_popular_ticket = "Business Class - Tokyo to London";
};

// Global game state (in a real game, this would be managed better)
extern GameState g_game_state;
