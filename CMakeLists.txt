cmake_minimum_required(VERSION 3.0)
project(frantic C)

find_package(PkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)

include_directories("${SDL2_INCLUDE_DIRS}")
link_directories("${SDL2_LIBRARY_DIRS}")

add_executable(frantic
    src/input.c
    src/main.c
    src/ship.c
    src/timer.c
)

target_link_libraries(frantic ${SDL2_LIBRARIES})

file(COPY src/assets DESTINATION .)
