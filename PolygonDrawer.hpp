#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"
#include "Polygon.hpp"
#include "Render.hpp"

using namespace std;
using namespace sf;

// proper pointers init !!!!!
class PolygonDrawer
{
public:
    bool drawingStarted = false;
    Polygon *polygon;
    Point *prevPoint;
    Render &render;

    bool firstIterationAfterClicking = false;

    PolygonDrawer(Render &render) : render(render) {}

    void mouseClickHandler(const Point &cursorPoint)
    {
        firstIterationAfterClicking = true;

        if (!drawingStarted)
            firstVertex(cursorPoint);
        else
            anotherVertex(cursorPoint);
    }

    void firstVertex(const Point &cursorPoint)
    {
        drawingStarted = true;

        polygon = new Polygon(cursorPoint);
        render.addPolygon(polygon);
        polygon->addVertex(cursorPoint);

        prevPoint = new Point(cursorPoint.x, cursorPoint.y);
    }

    void anotherVertex(const Point &cursorPoint)
    {
        // Removing temporary segment
        polygon->popSegment();
        polygon->popVertex();

        // checking wheter user clicked the start vertex
        if (polygon->start.pointInCircle(cursorPoint))
        {
            // drawing is being finished
            drawingStarted = false;

            polygon->addSegment(*prevPoint, polygon->start);
            delete prevPoint;
            prevPoint = nullptr;

            cout << "Drawing has been finished" << endl;
            printPolygon();
        }
        else
        {
            // adding new segment to the polygon
            polygon->addSegment(*prevPoint, cursorPoint);
            polygon->addVertex(cursorPoint);

            delete prevPoint;
            prevPoint = new Point(cursorPoint.x, cursorPoint.y);
        }
    }

    void temporarySegmentHanlder()
    {
        if (drawingStarted)
        {
            // adding a temporary segment
            Point cursorPoint(dtc(Point(Mouse::getPosition(window).x, Mouse::getPosition(window).y)));

            // after first iteration there is no previous temporary segment
            if (firstIterationAfterClicking)
                firstIterationAfterClicking = false;
            else
            {
                // removing previous temporary segment
                polygon->popVertex();
                polygon->popSegment();
            }

            polygon->addSegment(*prevPoint, cursorPoint);
            polygon->addVertex(cursorPoint);
        }
    }

    void printPolygon()
    {
        for (Segment &segment : polygon->segments)
            cout << segment.b << " " << segment.e << endl;
        cout << endl;
        for (Point &vertex : polygon->vertexes)
            cout << vertex << endl;
    }
};