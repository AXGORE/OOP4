cmake_minimum_required(VERSION 3.20)
project(big_project)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(big_project dialog/main.cpp Creature.hpp Creature.cpp Field.hpp Field.cpp Summoner.h Summoner.cpp Vector.hpp dialog/Dialog.h dialog/Dialog.cpp )

target_link_libraries(big_project sfml-graphics sfml-audio)