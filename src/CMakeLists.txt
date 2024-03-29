cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -s")

include_directories(${snake_SOURCE_DIR}/include)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(SHARE_SRC_FILES FoodBuilder.cpp Game.cpp AbstractGraphics.cpp BorderFrame.cpp Snake.cpp)
add_library(shareobjects OBJECT ${SHARE_SRC_FILES})

find_package(SDL2)
if(SDL2_FOUND)
	find_package(SDL2_image)
	if (SDL2_IMAGE_FOUND)
		file(COPY ../images DESTINATION .)
		set(SDL2_SRC_FILES graphics/SdlGraphics.cpp snake-sdl.cpp)
		include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
		add_executable(snake-sdl $<TARGET_OBJECTS:shareobjects> ${SDL2_SRC_FILES} )
		target_link_libraries(snake-sdl ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
	else()
		message(WARNING "SDL2_image is not found.")
	endif()
else()
    message(WARNING "SDL2 is not found.")
endif()

find_package(Curses)
if(Curses_FOUND)
	set(NCURSES_SRC_FILES graphics/NCursesGraphics.cpp snake-ncurses.cpp)
	include_directories(${Curses_INCLUDE_DIRS})
	add_executable(snake-ncurses $<TARGET_OBJECTS:shareobjects> ${NCURSES_SRC_FILES} )
	target_link_libraries(snake-ncurses ${CURSES_LIBRARIES})
else()
    message(WARNING "Curses is not found.")
endif()


find_package(OpenGL)
find_package(GLUT)
if(OpenGL_FOUND AND GLUT_FOUND)
	set(OPENGL_SRC_FILES graphics/OpenGlGraphics.cpp snake-glut.cpp)
	include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})
	add_executable(snake-glut $<TARGET_OBJECTS:shareobjects> ${OPENGL_SRC_FILES})
	target_link_libraries(snake-glut ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
else()
    message(WARNING "OpenGL and Glut are not found.")
endif()

#if(NOT(Curses_FOUND OR SDL2_FOUND OR (OpenGL_FOUND AND GLUT_FOUND)))
#    message(FATAL_ERROR "You have to install at least one of the packages!")
#endif()

set(NO_LIB_LINUX_SRC_FILES graphics/NoLibLinuxGraphics.cpp snake-nolib-lnx.cpp)
add_executable(snake-nolib-lnx $<TARGET_OBJECTS:shareobjects> ${NO_LIB_LINUX_SRC_FILES})
