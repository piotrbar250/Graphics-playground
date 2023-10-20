#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "global.hpp"
#include "Line.cpp"
#include "Polygon.cpp"
#include "Render.cpp"
#include "PolygonDrawer.cpp"

using namespace std;
using namespace sf;

RenderWindow window;

int main()
{
    window.create(sf::VideoMode(1152, 720), "Polygon editor");
    window.display();

    Mode currentMode = DRAWING;
    Render render;

    PolygonDrawer polygonDrawer(render);

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
                currentMode = EDITING;
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

                }
            }
        }

        if (currentMode == DRAWING)
        {
            polygonDrawer.temporarySegmentHanlder();
        }

        window.clear();

        render.draw();

        window.display();
    }
}