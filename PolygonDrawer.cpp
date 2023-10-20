#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"
#include "Polygon.cpp"
#include "Render.cpp"

using namespace std;
using namespace sf;

class PolygonDrawer
{
public:
    bool drawingStarted = false;
    Polygon *polygon;
    Point *prevPoint;
    Render& render;
    PolygonDrawer(Render &render) : render(render) {}
    void mouseClickHandler(const Point &cursorPoint)
    {
        if (!drawingStarted)
        {
            polygon = new Polygon(cursorPoint);
            render.addPolygon(polygon);
            drawingStarted = true;

            prevPoint = new Point(cursorPoint.x, cursorPoint.y);
        }
        else
        {
            polygon->addSegment(*prevPoint, cursorPoint);
            delete prevPoint;
            if (polygon->start.pointInCircle(cursorPoint))
            {
                drawingStarted = false;
                polygon->popVertex();
            }
            else
            {
                polygon->addVertex(cursorPoint);
                prevPoint = new Point(cursorPoint.x, cursorPoint.y);
            }
        }
    }

    void temporarySegmentHanlder()
    {
        if (drawingStarted)
        {
            Point cursorPoint(ctd(Point(Mouse::getPosition(window).x, Mouse::getPosition(window).y)));

            if (polygon->vertexes.size() > 1)
                polygon->popVertex();
            if (polygon->segments.size() > 0)
                polygon->popSegment();

            polygon->addVertex(cursorPoint);
            polygon->addSegment(*prevPoint, cursorPoint);
        }
    }
};

class PolygonEditor
{

};