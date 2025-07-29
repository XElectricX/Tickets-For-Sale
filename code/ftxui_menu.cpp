#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace ftxui;

int main() {
    // Create menu entries
    std::vector<std::string> entries = {
        "Start Game",
        "Load Game",
        "Options",
        "Exit"
    };

    int selected = 0;

    // Create a simple menu component
    auto menu = Menu(&entries, &selected);

    // Create the screen
    auto screen = ScreenInteractive::TerminalOutput();

    // Simple renderer without complex features
    auto renderer = Renderer(menu, [&] {
        return vbox({
            text("Game Menu") | center,
            separator(),
            menu->Render()
        }) | border;
    });

    screen.Loop(renderer);

    std::cout << "Selected: " << entries[selected] << std::endl;
    return 0;
}
