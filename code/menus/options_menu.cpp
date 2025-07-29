#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <vector>
#include <string>
#include "menu_system.h"

using namespace ftxui;

int show_options_menu() {
    // Define settings options
    bool difficulty_normal = true;
    bool sound_enabled = true;
    bool fullscreen = false;

    // Create toggles for different options
    auto difficulty_toggle = Toggle("Normal", "Hard", &difficulty_normal);
    auto sound_toggle = Toggle("On", "Off", &sound_enabled);
    auto display_toggle = Toggle("Windowed", "Fullscreen", &fullscreen);

    // Create a back button
    std::string back_label = "Back";
    auto back_button = Button(&back_label, [&] { return true; });

    // Arrange components in a vertical layout
    auto layout = Container::Vertical({
        Container::Horizontal({
            Renderer([] { return text("Difficulty: ") | vcenter; }),
            difficulty_toggle,
        }),
        Container::Horizontal({
            Renderer([] { return text("Sound: ") | vcenter; }),
            sound_toggle,
        }),
        Container::Horizontal({
            Renderer([] { return text("Display: ") | vcenter; }),
            display_toggle,
        }),
        Renderer([]{return separator();}),
        back_button,
    });

    bool exit_menu = false;
    back_button->on_click = [&] {
        exit_menu = true;
        return true;
    };

    auto screen = ScreenInteractive::TerminalOutput();

    auto renderer = Renderer(layout, [&] {
        return vbox({
            text("⚙️ OPTIONS ⚙️") | bold | center,
            separator(),
            hbox({
                text("Configure game settings") | center,
            }),
            separator(),
            layout->Render(),
            filler(),
            separator(),
            text("Use Tab to navigate, Enter to select, arrow keys to change options") | dim | center
        }) | border;
    });

    // Exit the menu loop when back button is clicked
    layout->on_change = [&] {
        if (exit_menu) {
            screen.ExitLoopClosure()();
        }
    };

    screen.Loop(renderer);

    // Return to main menu
    return MENU_BACK;
}
