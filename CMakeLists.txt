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
#include_directories(${SDL_INCLUDE_DIRS})

file(GLOB SRC_FILES "*.cpp")

add_executable(snake-game ${SRC_FILES})
#target_link_libraries(snake-game ${CURSES_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(snake-game ${CURSES_LIBRARIES} ${SDL2_LIBRARIES})
#target_link_libraries(snake-game ${CURSES_LIBRARIES} ${SDL_LIBRARY})
