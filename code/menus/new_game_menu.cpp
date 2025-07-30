#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include "code/game.h"
#include "base_menu.h"
#include "menu_system.h"

using namespace ftxui;
using std::string;

class NewGameMenu : public BaseMenu {
public:
	NewGameMenu() : BaseMenu("🆕 NEW GAME", "Enter your details", "new_game_menu") {
		// No options, just fields and a button
	}

	int show()
	{
		#ifdef _WIN32
			system("cls");
		#else
			system("clear");
		#endif

		std::string player_name, business_name;
		bool start_pressed = false;
		std::string error_msg;
		auto input_player = Input(&player_name, "Player Name");
		auto input_business = Input(&business_name, "Business Name");
		auto screen = ScreenInteractive::TerminalOutput();
		auto start_button = Button("Start Game", [&] {
			if (player_name.empty() || business_name.empty()) {
				error_msg = "Fields cannot be empty!";
			} else {
				game_data = Game{};
				game_data.player_name = player_name;
				game_data.business_name = business_name;
				start_pressed = true;
				screen.Exit(); // <-- This will exit the FTXUI loop!
			}
		});
		auto layout = Container::Vertical({input_player, input_business, start_button});
		// Copilot: Wrap in CatchEvent to ensure button works with Enter and mouse
		auto root = CatchEvent(layout, [&](const Event& event) {
			if (event == Event::Return && start_button->Active()) {
				start_button->OnEvent(Event::Return);
				return true;
			}
			return false;
		});
		auto renderer = Renderer(root, [&] {
			Elements elems = {
				text("🆕 NEW GAME") | bold | center | color(Color::Cyan),
				separator(),
				hbox({text("Player Name: "), input_player->Render()}),
				hbox({text("Business Name: "), input_business->Render()}),
			};
			if (!error_msg.empty())
				elems.push_back(text(error_msg) | color(Color::Red));
			elems.push_back(separator());
			elems.push_back(start_button->Render() | center);
			return vbox(elems) | border;
		});
		int result = 0;
		screen.Loop(renderer);
		if (start_pressed)
			result = MENU_TICKET_COUNTER;
		else
			result = MENU_START_GAME;
		return result;
	}
};

int show_new_game_menu()
{
	NewGameMenu menu;
	return menu.show();
}
