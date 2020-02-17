cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
#add_compile_options(-Wall -Wextra -pedantic -g)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall  -Wextra -pedantic -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -pedantic")

include_directories(${snake_SOURCE_DIR}/include)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(SHARE_SRC_FILES FoodBuilder.cpp Game.cpp AbstractGraphics.cpp BorderFrame.cpp Snake.cpp)

find_package(SDL2)
if(SDL2_FOUND)
	set(SDL2_SRC_FILES ${SHARE_SRC_FILES} graphics/SdlGraphics.cpp snake-sdl.cpp)
	include_directories(${SDL2_INCLUDE_DIRS})
	add_executable(snake-sdl ${SDL2_SRC_FILES})
	target_link_libraries(snake-sdl ${SDL2_LIBRARIES})
else()
    message(WARNING "SDL2 not found.")
endif()

find_package(Curses)
if(Curses_FOUND)
	set(NCURSES_SRC_FILES ${SHARE_SRC_FILES} graphics/NCursesGraphics.cpp snake-ncurses.cpp)
	include_directories(${Curses_INCLUDE_DIRS})
	add_executable(snake-ncurses ${NCURSES_SRC_FILES})
	target_link_libraries(snake-ncurses ${CURSES_LIBRARIES})
else()
    message(WARNING "Curses not found.")
endif()

if(NOT(Curses_FOUND OR SDL2_FOUND))
    message(FATAL_ERROR "You have to install at least one of the packages!")
endif()
