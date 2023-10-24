#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "global.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Polygon.hpp"
#include "Render.hpp"
#include "PolygonDrawer.hpp"
#include "PolygonEditor.hpp"
#include "PolygonVertexRemovingEditor.hpp"
#include "PolygonVertexInsertingEditor.hpp"
#include "PolygonMovingEditor.hpp"
#include "ButtonDrawer.hpp"
#include "VerticalRelationEditor.hpp"
#include "HorizontalRelationEditor.hpp"
#include "AdjacentEdgesRelationEditor.hpp"
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
    PolygonVertexInsertingEditor* polygonVertexInsertingEditor;
    PolygonMovingEditor* polygonMovingEditor;

    ButtonDrawer buttonDrawer(render);
    
    VerticalRelationEditor verticalRelationEditor(render);
    HorizontalRelationEditor horizontalRelationEditor(render);
    AdjacentEdgesRelationEditor adjacentEdgesRelationEditor(render);
    // buttonDrawer.createButton();

    bool displayRelationMenu = false;

    bool polygonStarted = false;

    int i = 0;
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
            if(event.type == Event::KeyPressed and event.key.code == Keyboard::I)
            {
                polygonVertexInsertingEditor = new PolygonVertexInsertingEditor(render);
                currentMode = VERTEX_INSERTING;
            }
            if(event.type == Event::KeyPressed and event.key.code == Keyboard::M)
            {
                polygonMovingEditor = new PolygonMovingEditor(render);
                currentMode = POLYGON_MOVING;
            }
            if(event.type == Event::KeyPressed and event.key.code == Keyboard::D)
            {
                displayRelationMenu = !displayRelationMenu;
            }
            if(event.type == Event::KeyPressed and event.key.code == Keyboard::X)
            {
                // polygonMovingEditor = new PolygonMovingEditor(render);
                if(currentMode == DRAWING)
                    currentMode = TESTING;
                else if(currentMode == TESTING)
                    currentMode = DRAWING;
                else
                {
                    cout << "UNDEFINED BEHAVIOUR" << endl;
                    return 0;
                }
            }
            

            if (event.type == Event::MouseButtonPressed)
            {
                Point cursorPoint(Point::ctd(Point(event.mouseButton.x, event.mouseButton.y)));

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
                else if(currentMode == VERTEX_INSERTING)
                {
                    polygonVertexInsertingEditor->mouseClickHandler(cursorPoint);
                    // delete polygonVertexInsertingEditor;
                }
                else if(currentMode == POLYGON_MOVING)
                {
                    polygonMovingEditor->mouseClickHandler(cursorPoint);
                    // delete polygonVertexInsertingEditor;
                }
                else if(currentMode == TESTING)
                {
                    buttonDrawer.mouseClickHandler(cursorPoint);
                    // delete polygonVertexInsertingEditor;
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
        else if(currentMode == POLYGON_MOVING)
        {
            polygonMovingEditor->temporaryPolygonHandler();
        }

        if(displayRelationMenu)
        {
            cout << "weszlem " << i++ << endl;
            buttonDrawer.displayRelationMenu();
        }

        // adjacentEdgesRelationEditor.adjustRelations(polygonDrawer);
        verticalRelationEditor.adjustPlain(polygonDrawer);
        horizontalRelationEditor.adjustPlain(polygonDrawer);
        adjacentEdgesRelationEditor.adjustPlain(polygonDrawer);
        window.clear();

        render.draw();

        window.display();
    }
}