cmake_minimum_required(VERSION 3.3)
project(Hangman)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(SOURCE_FILES
        src/main.cpp
        src/scenes/scene.h
        src/scenes/mainmenu.cpp
        src/scenes/mainmenu.h
        src/util/assetmanager.cpp
        src/util/assetmanager.h
        src/scenes/game.cpp
        src/scenes/game.h
        src/gameobjects/ui/button.cpp
        src/gameobjects/ui/button.h
        src/gameobjects/gameobject.h
        src/scenes/help.cpp
        src/scenes/help.h
        )

add_executable(Hangman ${SOURCE_FILES})

include_directories(${ALLEGRO_INCLUDE_DIR})
target_link_libraries(Hangman
        allegro allegro_image allegro_font
        allegro_primitives allegro_ttf allegro_audio
        allegro_dialog allegro_memfile allegro_acodec
        allegro_color allegro_main allegro_physfs
        )
