cmake_minimum_required(VERSION 3.3)
project(Hangman)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(SOURCE_FILES
        main.cpp)

add_executable(Hangman ${SOURCE_FILES})

include_directories(${ALLEGRO_INCLUDE_DIR})
target_link_libraries(Hangman allegro allegro_image allegro_font
        allegro_primitives allegro_ttf allegro_audio
        allegro_dialog allegro_memfile allegro_acodec
        allegro_color allegro_main allegro_physfs)