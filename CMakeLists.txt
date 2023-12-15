cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")
cmake_path(SET LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")


set(TARGET "chess")

project(${TARGET} LANGUAGES CXX)

set(FLTK_SKIP_FLUID True)
set(OpenGL_GL_PREFERENCE "GLVND")

find_package(FLTK REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
        ${LIB_DIR}
        ${GRAPHLIB_DIR}
        SYSTEM
        ${FLTK_INCLUDE_DIR}
)

link_directories(
        ${FLTK_INCLUDE_DIR}/../lib
)

add_executable(
        ${TARGET}
        main.cpp
        board.h
        board.cpp
        cell.h
        cell.cpp
        ${LIB_DIR}/Graph_lib/fltk.h
        ${LIB_DIR}/Graph_lib/Graph.h
        ${LIB_DIR}/Graph_lib/GUI.h
        ${LIB_DIR}/Graph_lib/Point.h
        ${LIB_DIR}/Graph_lib/Simple_window.h
        ${LIB_DIR}/Graph_lib/Window.h
        ${LIB_DIR}/Graph_lib/Graph.cpp
        ${LIB_DIR}/Graph_lib/GUI.cpp
        ${LIB_DIR}/Graph_lib/Window.cpp
        figures.h
        figures.cpp
        constants.h
        game_position.h
        game_position.cpp

)

target_link_libraries(
        ${TARGET}
        ${FLTK_LIBRARIES}
        ${OPENGL_LIBRARIES}
)

if(WIN32)
    target_link_libraries(
            ${TARGET}
            fltk_jpeg
            fltk_png
            fltk_z
    )
endif()

install(TARGETS ${TARGET})