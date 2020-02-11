cmake_minimum_required (VERSION 2.6)

project (snake-game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
#add_compile_options(-Wall -Wextra -pedantic -g)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall  -Wextra -pedantic -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -pedantic")

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(Curses REQUIRED)
find_package(SDL2 REQUIRED)
#find_package(SDL2_image )
include_directories(${SDL2_INCLUDE_DIRS})
#include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

set(SHARE_SRC_FILES FoodBuilder.cpp Game.cpp AbstractGraphics.cpp BorderFrame.cpp Snake.cpp)
set(NCURSES_SRC_FILES ${SHARE_SRC_FILES} NCursesGraphics.cpp snake-ncurses.cpp)
set(SDL2_SRC_FILES ${SHARE_SRC_FILES} SdlGraphics.cpp snake-sdl.cpp)
add_executable(snake-ncurses ${NCURSES_SRC_FILES})
add_executable(snake-sdl ${SDL2_SRC_FILES})
target_link_libraries(snake-ncurses ${CURSES_LIBRARIES})
target_link_libraries(snake-sdl ${SDL2_LIBRARIES})
