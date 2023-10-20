cmake_minimum_required(VERSION 3.10)
project(program)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(program program.cpp global.hpp Point.cpp Line.cpp Polygon.cpp Render.cpp PolygonDrawer.cpp)
target_link_libraries(program sfml-graphics sfml-window sfml-system)