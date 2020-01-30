cmake_minimum_required (VERSION 2.6)

project (snake-game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -pedantic)

find_package(Curses)

file(GLOB SRC_FILES "*.cpp")

add_executable(snake-game ${SRC_FILES})
target_link_libraries(snake-game ${CURSES_LIBRARIES})
