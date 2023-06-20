cmake_minimum_required(VERSION 3.24)
project(Projekt)
set(CMAKE_CXX_STANDARD 23)

add_executable(Projekt main.cpp Menu/Menu.cpp Menu/Menu.h Board/Board.cpp Board/Board.h Board/Hex.cpp Board/Hex.h SaveGame/SaveGame.cpp SaveGame/SaveGame.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(Projekt sfml-system sfml-window sfml-graphics sfml-audio stdc++fs)
