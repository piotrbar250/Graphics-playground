#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"
#include "Polygon.hpp"
#include "Render.hpp"

using namespace std;
using namespace sf;

class PolygonEditor
{
public:
    bool editingStarted = false;
    Render &render;
    Polygon *selectedPolygon = nullptr;
    Point *selectedPoint = nullptr;
    Segment *adjacentSegments[2];
    Point *adjacentSegmentsPoints[2];

    PolygonEditor(Render &render) : render(render)
    {
        for (int i = 0; i < 2; i++)
        {
            adjacentSegments[i] = nullptr;
            adjacentSegmentsPoints[i] = nullptr;
        }
    }

    void findPoint(const Point &cursorPoint)
    {
        for (Polygon *&polygon : render.polygons)
        {
            for (Point &vertex : polygon->vertexes)
            {
                if (vertex.pointInCircle(cursorPoint))
                {
                    selectedPoint = &vertex;
                    selectedPolygon = polygon;
                }
            }
        }
    }

    void findAdjacentSegmentPoints(const Point &cursor)
    {
        for (Segment &segment : selectedPolygon->segments)
        {
            if (segment.b == *selectedPoint)
            {

                if (!adjacentSegmentsPoints[0])
                    adjacentSegmentsPoints[0] = &(segment.b);
                else
                    adjacentSegmentsPoints[1] = &(segment.b);
            }

            if (segment.e == *selectedPoint)
            {
                if (!adjacentSegmentsPoints[0])
                    adjacentSegmentsPoints[0] = &(segment.e);
                else
                    adjacentSegmentsPoints[1] = &(segment.e);
            }
        }
    }

    void finishEditing()
    {
        editingStarted = false;
        currentMode = DRAWING;
    }

    void placeCursor(const Point &cursorPoint)
    {
        *(adjacentSegmentsPoints[0]) = cursorPoint;
        *(adjacentSegmentsPoints[1]) = cursorPoint;
        *selectedPoint = cursorPoint;
    }

    void mouseClickHandler(const Point &cursorPoint)
    {
        if (!editingStarted)
        {
            editingStarted = true;

            findPoint(cursorPoint);

            if (selectedPoint)
                findAdjacentSegmentPoints(cursorPoint);
            else
                finishEditing();
        }
        else
        {
            placeCursor(cursorPoint);
            finishEditing();
        }
    }

    void temporarySegmentHanlder()
    {
        if (editingStarted)
        {
            Point cursorPoint(dtc(Point(Mouse::getPosition(window).x, Mouse::getPosition(window).y)));
            placeCursor(cursorPoint);
        }
    }
};