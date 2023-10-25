#include "App.hpp"

void App::handleAllEvents()
{
    Event event;

    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();

        if (event.type == Event::KeyPressed and event.key.code == Keyboard::E)
        {
            polygonEditor = new PolygonEditor(render);
            currentMode = EDITING;
        }
        if (event.type == Event::KeyPressed and event.key.code == Keyboard::R)
        {
            polygonVertexRemovingEditor = new PolygonVertexRemovingEditor(render);
            currentMode = VERTEX_REMOVING;
        }
        if (event.type == Event::KeyPressed and event.key.code == Keyboard::I)
        {
            polygonVertexInsertingEditor = new PolygonVertexInsertingEditor(render);
            currentMode = VERTEX_INSERTING;
        }
        if (event.type == Event::KeyPressed and event.key.code == Keyboard::M)
        {
            polygonMovingEditor = new PolygonMovingEditor(render);
            currentMode = POLYGON_MOVING;
        }
        if (event.type == Event::KeyPressed and event.key.code == Keyboard::D)
        {
            displayRelationMenu = !displayRelationMenu;
        }
        if (event.type == Event::KeyPressed and event.key.code == Keyboard::X)
        {
            swapModes(DRAWING, TESTING);
        }
        if (event.type == Event::KeyPressed and event.key.code == Keyboard::S)
        {
            swapModes(DRAWING, SLIDER);
        }
        if (event.type == Event::KeyPressed and event.key.code == Keyboard::A)
        {
            swapModes(LIBRARY, BRESENHAM);
        }

        slider.handleEvent(event);
        if (event.type == Event::MouseButtonPressed)
        {
            Point cursorPoint(Point::ctd(Point(event.mouseButton.x, event.mouseButton.y)));

            if (currentMode == DRAWING)
            {
                polygonDrawer.mouseClickHandler(cursorPoint);
            }
            else if (currentMode == EDITING)
            {
                polygonEditor->mouseClickHandler(cursorPoint);
            }
            else if (currentMode == VERTEX_REMOVING)
            {
                polygonVertexRemovingEditor->mouseClickHandler(cursorPoint);
            }
            else if (currentMode == VERTEX_INSERTING)
            {
                polygonVertexInsertingEditor->mouseClickHandler(cursorPoint);
            }
            else if (currentMode == POLYGON_MOVING)
            {
                polygonMovingEditor->mouseClickHandler(cursorPoint);
            }
            else if (currentMode == TESTING)
            {
                buttonDrawer.mouseClickHandler(cursorPoint);
            }
        }
    }
}