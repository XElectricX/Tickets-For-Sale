project('tickets for sale', 'cpp', default_options : ['cpp_std=c++17'])

json_dep = dependency('nlohmann_json', fallback: ['nlohmann_json', 'nlohmann_json_dep'])

# Try to find FTXUI using pkgconfig first, then fallback to manual approach
ftxui_dep = []
ftxui_found = false

# Check if we can find FTXUI via pkg-config
ftxui_component_dep = dependency('ftxui-component', required: false, fallback: ['ftxui', 'component_dep'])
ftxui_dom_dep = dependency('ftxui-dom', required: false, fallback: ['ftxui', 'dom_dep'])
ftxui_screen_dep = dependency('ftxui-screen', required: false, fallback: ['ftxui', 'screen_dep'])

if ftxui_component_dep.found() and ftxui_dom_dep.found() and ftxui_screen_dep.found()
    ftxui_dep = [ftxui_component_dep, ftxui_dom_dep, ftxui_screen_dep]
    ftxui_found = true
endif

srcs = [
	'main.cpp',
	'code/helpers.cpp',
	'code/game.cpp',
	'code/save_system.cpp',
	'code/objects/tickets.cpp',
	'code/objects/customers.cpp',
	'code/menus/base_menu.cpp',
	'code/menus/game_state.cpp',
	'code/menus/barter_menu.cpp',
	'code/menus/main_menu.cpp',
	'code/menus/options_menu.cpp',
	'code/menus/statistics_menu.cpp',
	'code/menus/ticket_counter_menu.cpp',
	'code/menus/ticket_inventory_menu.cpp',
	'code/menus/ticket_purchasing_menu.cpp',
	'code/menus/menu_state_manager.cpp',
	'code/menus/settings_manager.cpp',
]

# Main executable with FTXUI support
if ftxui_found
    executable('tickets-for-sale', srcs,
               dependencies: [json_dep, ftxui_component_dep, ftxui_dom_dep, ftxui_screen_dep],
               override_options: ['cpp_std=c++17'])
else
    executable('tickets-for-sale', srcs, dependencies: [json_dep])
endif
