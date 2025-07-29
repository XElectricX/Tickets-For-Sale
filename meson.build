project('tickets for sale', 'cpp', default_options : ['cpp_std=c++17'])

# Stupid thing has to be forced to use C++17 for some reason
if meson.get_compiler('cpp').get_id() == 'msvc'
  add_project_arguments('/std:c++17', language : 'cpp')
endif

json_dep = dependency('nlohmann_json', fallback: ['nlohmann_json', 'nlohmann_json_dep'])

srcs = [
	'main.cpp',
	'code/helpers.cpp',
	'code/game.cpp',
	'code/save_system.cpp',
	'code/objects/tickets.cpp',
	'code/objects/customers.cpp',
	'code/menus/barter_menu.cpp',
	'code/menus/main_menu.cpp',
	'code/menus/save_system_menus.cpp',
	'code/menus/ticket_counter_menu.cpp',
	'code/menus/ticket_inventory_menu.cpp',
	'code/menus/ticket_purchasing_menu.cpp',
]

executable('tickets-for-sale', srcs, dependencies : [json_dep])