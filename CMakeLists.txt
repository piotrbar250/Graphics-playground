cmake_minimum_required(VERSION 3.10)
project(program)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(program program.cpp global.hpp App.hpp Point.hpp Point.cpp Line.hpp Line.cpp Polygon.hpp Render.hpp PolygonDrawer.hpp PolygonEditor.hpp PolygonVertexRemovingEditor.hpp PolygonVertexInsertingEditor.hpp PolygonMovingEditor.hpp Button.hpp ButtonDrawer.hpp VerticalRelationEditor.hpp HorizontalRelationEditor.hpp AdjacentEdgesRelationEditor.hpp NaiveDrawingLineAlgorithm.hpp BresenhamDrawingLineAlgorithm.hpp CircularSector.hpp Slider.hpp WuDrawingLineAlgorithm.hpp IO.hpp)
target_link_libraries(program sfml-graphics sfml-window sfml-system)