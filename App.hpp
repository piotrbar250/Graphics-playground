#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>
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
#include "NaiveDrawingLineAlgorithm.hpp"
#include "BresenhamDrawingLineAlgorithm.hpp"
#include "CircularSector.hpp"
#include "Slider.hpp"
#include "IO.hpp"

using namespace std;
using namespace sf;

RenderWindow window;
Mode currentMode;
Algorithm currentAlgorithm;
float offsetThickness;

class App
{
public:
    bool displayRelationMenu;
    bool polygonStarted;

    Render render;

    PolygonDrawer polygonDrawer;
    PolygonEditor *polygonEditor;
    PolygonVertexRemovingEditor *polygonVertexRemovingEditor;
    PolygonVertexInsertingEditor *polygonVertexInsertingEditor;
    PolygonMovingEditor *polygonMovingEditor;

    ButtonDrawer buttonDrawer;

    VerticalRelationEditor verticalRelationEditor;
    HorizontalRelationEditor horizontalRelationEditor;
    AdjacentEdgesRelationEditor adjacentEdgesRelationEditor;

    Slider slider;

    App() : polygonDrawer(render), buttonDrawer(render), verticalRelationEditor(render),
            horizontalRelationEditor(render), adjacentEdgesRelationEditor(render)
    {
        offsetThickness = 1;
        displayRelationMenu = polygonStarted = false;

        polygonEditor = new PolygonEditor(render);
        polygonVertexRemovingEditor = nullptr;
        polygonVertexInsertingEditor = nullptr;
        polygonMovingEditor = nullptr;
    }

    void run()
    {
        setup();
        loop();
    }

    void setup()
    {
        window.create(sf::VideoMode(1152, 720), "Polygon editor");
        window.display();
    }

    void loop()
    {
        while (window.isOpen())
        {
            handleAllEvents();
            handleCurrentModeLogic();
            renderFrame();
        }
    }

    void handleAllEvents()
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
            if (event.type == Event::KeyPressed and event.key.code == Keyboard::W)
            {
                swapModes(LIBRARY, WU);
            }
            if (event.type == Event::KeyPressed and event.key.code == Keyboard::Z)
            {
                savePolygons(render.polygons, "../poligons.txt");
            }
            if (event.type == Event::KeyPressed and event.key.code == Keyboard::L)
            {
                render.polygons = loadPolygons("../poligons.txt");
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

    void handleCurrentModeLogic()
    {

        if (currentMode == DRAWING)
        {
            polygonDrawer.temporarySegmentHanlder();
        }
        else if (currentMode == EDITING)
        {
            polygonEditor->temporarySegmentHanlder();
        }
        else if (currentMode == POLYGON_MOVING)
        {
            polygonMovingEditor->temporaryPolygonHandler();
        }

        if (displayRelationMenu)
        {
            buttonDrawer.displayRelationMenu();
        }
    }

    void renderFrame()
    {
        verticalRelationEditor.adjustPlain(polygonDrawer);
        horizontalRelationEditor.adjustPlain(polygonDrawer);
        adjacentEdgesRelationEditor.adjustPlain(polygonDrawer);
        createCircularSectors(render);
        window.clear();
    
        render.draw();
        slider.draw(window);

        window.display();
    }
    
    template <typename T>
    void swapValues(T& currentValue, T value1, T value2)
    {
        if (currentValue == value1)
            currentValue = value2;
        else
            currentValue = value1;
    }

    template<typename T> 
    void swapModes(T value1, T value2)
    {
        if constexpr (is_same_v<T, Mode>)
        {
            swapValues(currentMode, value1, value2);
        }
        else if constexpr (is_same_v<T, Algorithm>)
        {
            swapValues(currentAlgorithm, value1, value2);
        }
    }
};