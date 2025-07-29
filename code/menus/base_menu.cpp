#include "base_menu.h"
#include <algorithm>
#include <cctype>

BaseMenu::BaseMenu(const std::string &title, const std::string &subtitle, const std::string &menu_id)
    : title(title), subtitle(subtitle), menu_id(menu_id), footer_text("Use arrow keys, hotkeys, or Enter to select")
{
}

void BaseMenu::add_option(const std::string &text, char hotkey, int return_value, std::function<void()> action)
{
    options.push_back({text, hotkey, return_value, action});
}

void BaseMenu::add_status_info(const std::string &info)
{
    status_info.push_back(info);
}

void BaseMenu::set_footer(const std::string &text)
{
    footer_text = text;
}

void BaseMenu::set_theme_colors(Color title, Color subtitle, Color hotkey, Color status)
{
    title_color = title;
    subtitle_color = subtitle;
    hotkey_color = hotkey;
    status_color = status;
}

int BaseMenu::show()
{
    int selected = 0;
    std::vector<std::string> menu_strings;

    // Populate menu strings
    for (const auto &option : options)
    {
        menu_strings.push_back(option.text);
    }

    // Use persisted selection if available and persistence is enabled
    if (!menu_id.empty() && persist_selection)
    {
        selected = MenuStateManager::get_selection(menu_id);
        // Ensure the selection is valid for the current menu
        if (selected >= static_cast<int>(options.size()))
        {
            selected = 0;
        }
    }

    // Create the menu component with our selection variable
    auto menu = Menu(&menu_strings, &selected);

    // Create the screen early so we can reference it in the event handler
    auto screen = ScreenInteractive::TerminalOutput();

    // Create combined component with header, menu, status, and footer
    auto combined_component = Renderer(menu, [&]
                                       { return vbox({create_header(),
                                                      separator(),
                                                      menu->Render(), // This renders the actual interactive menu
                                                      separator(),
                                                      create_status_bar(),
                                                      separator(),
                                                      create_footer()}) |
                                                border; });

    // Handle keyboard shortcuts and custom events
    auto event_handler = CatchEvent(combined_component, [&](Event event)
                                    {
        // Handle Ctrl+C - in FTXUI, Ctrl+C is represented as character with ASCII code 3
        if (event.is_character() && event.character().size() == 1 &&
            static_cast<unsigned char>(event.character()[0]) == 3) {
            // This will break out of the screen loop, allowing the menu to return MENU_EXIT
            screen.ExitLoopClosure()();
            return true;
        }

        // Handle hotkeys (only regular character keys, not control characters)
        if (event.is_character()) {
            char pressed = event.character()[0];
            // Ignore control characters (ASCII < 32)
            if (static_cast<unsigned char>(pressed) >= 32) {
                pressed = std::tolower(pressed);
                for (size_t i = 0; i < options.size(); ++i) {
                    if (std::tolower(options[i].hotkey) == pressed) {
                        selected = static_cast<int>(i);
                        // Execute action and exit immediately for hotkeys
                        if (!menu_id.empty() && persist_selection) {
                            MenuStateManager::save_selection(menu_id, selected);
                        }
                        if (options[selected].action) {
                            options[selected].action();
                        }
                        screen.ExitLoopClosure()();
                        return true;
                    }
                }
            }
        }

        // Handle Enter key for selection
        if (event == Event::Return) {
            // Save selection and exit immediately
            if (!menu_id.empty() && persist_selection) {
                MenuStateManager::save_selection(menu_id, selected);
            }

            // Execute action if present
            if (selected >= 0 && selected < static_cast<int>(options.size())) {
                if (options[selected].action) {
                    options[selected].action();
                }
            }
            
            // Exit the screen loop to return from the menu
            screen.ExitLoopClosure()();
            return true;
        }

        // Allow derived classes to handle custom events
        return handle_custom_events(event); });

    screen.Loop(event_handler);

    // Save the selected index if we have a menu ID and persistence is enabled
    if (!menu_id.empty() && persist_selection)
    {
        MenuStateManager::save_selection(menu_id, selected);
    }

    // Execute action if present, then return the value
    if (selected >= 0 && selected < static_cast<int>(options.size()))
    {
        if (options[selected].action)
        {
            options[selected].action();
        }
        return options[selected].return_value;
    }

    return MENU_BACK; // Fallback
}

Element BaseMenu::create_header()
{
    if (subtitle.empty())
    {
        return text(title) | bold | center | color(title_color);
    }
    else
    {
        return vbox({text(title) | bold | center | color(title_color),
                     text(subtitle) | center | color(subtitle_color)});
    }
}

Element BaseMenu::create_menu_content()
{
    Elements menu_elements;

    for (size_t i = 0; i < options.size(); ++i)
    {
        auto option_text = format_option_text(options[i], false);
        menu_elements.push_back(option_text);
    }

    return vbox(menu_elements);
}

Element BaseMenu::create_status_bar()
{
    if (status_info.empty())
    {
        return text(" ") | dim; // Empty placeholder
    }

    Elements status_elements;
    for (size_t i = 0; i < status_info.size(); ++i)
    {
        status_elements.push_back(text(status_info[i]) | color(status_color));
        if (i < status_info.size() - 1)
        {
            status_elements.push_back(text(" | "));
        }
    }

    return hbox(status_elements) | center;
}

Element BaseMenu::create_footer()
{
    return text(footer_text) | dim | center;
}

bool BaseMenu::handle_custom_events(Event event)
{
    // Default implementation - no custom events
    return false;
}

Component BaseMenu::create_menu_component()
{
    std::vector<std::string> menu_strings;
    for (const auto &option : options)
    {
        menu_strings.push_back(option.text);
    }

    int selected = 0;

    // Use persisted selection if available and persistence is enabled
    if (!menu_id.empty() && persist_selection)
    {
        selected = MenuStateManager::get_selection(menu_id);
        // Ensure the selection is valid for the current menu
        if (selected >= static_cast<int>(options.size()))
        {
            selected = 0;
        }
    }

    return Menu(&menu_strings, &selected);
}

Element BaseMenu::format_option_text(const GameMenuOption &option, bool is_selected)
{
    if (option.hotkey != '\0')
    {
        std::string hotkey_str = "[";
        hotkey_str += std::toupper(option.hotkey);
        hotkey_str += "]";

        return hbox({text(option.text),
                     text(" "),
                     text(hotkey_str) | color(hotkey_color)});
    }
    else
    {
        return text(option.text);
    }
}
