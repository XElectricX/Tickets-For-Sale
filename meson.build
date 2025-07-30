project('tickets for sale', 'cpp', default_options: ['cpp_std=c++17'])

# Stupid thing has to be forced to use C++17 for some reason
if meson.get_compiler('cpp').get_id() == 'msvc'
	add_project_arguments('/std:c++17', language: 'cpp')
endif

json_dep = dependency('nlohmann_json', fallback: ['nlohmann_json', 'nlohmann_json_dep'])

# ftxui dependencies
ftxui_component_dep = dependency('ftxui-component', fallback: ['ftxui', 'component_dep'])
ftxui_dom_dep = dependency('ftxui-dom', fallback: ['ftxui', 'dom_dep'])
ftxui_screen_dep = dependency('ftxui-screen', fallback: ['ftxui', 'screen_dep'])

# Source files for the main executable
srcs = [
	'main.cpp',
	'code/helpers.cpp',
	'code/save_system.cpp',
	'code/objects/tickets.cpp',
	'code/objects/customers.cpp',
	'code/app/tickets_for_sale_app.cpp',
	'code/menus/base_menu.cpp',
	'code/menus/barter_menu.cpp',
	'code/menus/main_menu.cpp',
	'code/menus/new_game_menu.cpp',
	'code/menus/save_system_menus.cpp',
	'code/menus/ticket_counter_menu.cpp',
	'code/menus/ticket_inventory_menu.cpp',
	'code/menus/ticket_purchasing_menu.cpp',
	'code/menus/menu_state_manager.cpp',
]

#  Create the main executable
executable(
	'tickets-for-sale',
	srcs,
	dependencies: [json_dep, ftxui_component_dep, ftxui_dom_dep, ftxui_screen_dep],
	override_options: ['cpp_std=c++17'],
)

