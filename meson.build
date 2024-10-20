project('life_cpp', 'cpp', default_options: ['cpp_std=c23'])

sdl2 = meson.get_compiler('cpp').find_library('SDL2')

executable('game_of_life.x', ['main.cpp', 'GameState.cpp', 'Display.cpp' ], dependencies: [sdl2])
