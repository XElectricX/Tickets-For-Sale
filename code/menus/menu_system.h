#pragma once

#include <string>

// Forward declaration of BaseMenu
class BaseMenu;

// Menu function declarations
int show_main_menu();
int show_new_game_menu();
int show_ticket_counter_menu();
int show_ticket_inventory_menu();
int show_ticket_purchasing_menu();
int show_barter_menu();

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
	MENU_NEW_GAME = 13,

	// Game menus
	MENU_TICKET_COUNTER = 20,
	MENU_INVENTORY = 21,
	MENU_PURCHASE = 22,
	MENU_BARTER = 23,

	// Error states
	MENU_ERROR = -1
};
