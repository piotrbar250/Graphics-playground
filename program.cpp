#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "global.hpp"
#include "Line.cpp"
#include "Polygon.cpp"
#include "Render.cpp"
#include "PolygonDrawer.cpp"
#include "PolygonEditor.cpp"
#include "PolygonVertexRemovingEditor.cpp"

using namespace std;
using namespace sf;

RenderWindow window;
Mode currentMode;

int main()
{
    window.create(sf::VideoMode(1152, 720), "Polygon editor");
    window.display();

    currentMode = DRAWING;
    Render render;

    PolygonDrawer polygonDrawer(render);
    PolygonEditor* polygonEditor = new PolygonEditor(render);
    PolygonVertexRemovingEditor* polygonVertexRemovingEditor;
    bool polygonStarted = false;

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if(event.type == Event::KeyPressed and event.key.code == Keyboard::E)
            {
                polygonEditor = new PolygonEditor(render);
                currentMode = EDITING;
            }
            if(event.type == Event::KeyPressed and event.key.code == Keyboard::R)
            {
                polygonVertexRemovingEditor = new PolygonVertexRemovingEditor(render);
                currentMode = VERTEX_REMOVING;

            }
            if (event.type == Event::MouseButtonPressed)
            {
                Point cursorPoint(ctd(Point(event.mouseButton.x, event.mouseButton.y)));

                if (currentMode == DRAWING)
                {
                    polygonDrawer.mouseClickHandler(cursorPoint);
                }
                else if(currentMode == EDITING)
                {
                    polygonEditor->mouseClickHandler(cursorPoint);
                }
                else if(currentMode == VERTEX_REMOVING)
                {
                    polygonVertexRemovingEditor->mouseClickHandler(cursorPoint);
                }
            }
        }

        if (currentMode == DRAWING)
        {
            polygonDrawer.temporarySegmentHanlder();
        }
        else if(currentMode == EDITING)
        {
            polygonEditor->temporarySegmentHanlder();
        }

        window.clear();

        render.draw();

        window.display();
    }
}