#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"
#include "Polygon.hpp"
#include "Render.hpp"

using namespace std;
using namespace sf;

class PolygonMovingEditor
{
public:
    bool movingStarted = false;
    Polygon *selectedPolygon;
    Render &render;
    Point origin;
    Segment currentHorizontalSegment;
    vector<Point> orignalVertexes;
    vector<Segment> orignalSegments;

    PolygonMovingEditor(Render &render) : render(render) {}

    void mouseClickHandler(const Point &cursorPoint)
    {
        if (!movingStarted)
        {
            movingStarted = true;
            currentHorizontalSegment = Segment(cursorPoint, {M, cursorPoint.y});
            origin = cursorPoint;
            selectedPolygon = nullptr;

            findPolygon(cursorPoint);

            if (!selectedPolygon)
                finishEditing();
        }
        else
        {
            saveCurrentPolygon();
            finishEditing();
        }
    }

    void temporaryPolygonHandler()
    {
        if (movingStarted)
            saveCurrentPolygon();
    }

    void findPolygon(const Point &cursorPoint)
    {
        int cnt = 0;
        for (Polygon *&polygon : render.polygons)
        {
            for (Segment &segment : polygon->segments)
            {
                if (segment.intersect(currentHorizontalSegment))
                    cnt++;
            }
            if (cnt % 2 == 1)
            {
                selectedPolygon = polygon;
                orignalVertexes = polygon->vertexes;
                orignalSegments = polygon->segments;
                break;
            }
        }
    }

    void saveCurrentPolygon()
    {
        Point cursorPoint(dtc(Point(Mouse::getPosition(window).x, Mouse::getPosition(window).y)));

        vector<Point> tmpVertexes;
        for (Point &vertex : orignalVertexes)
            tmpVertexes.push_back(vertex + (cursorPoint - origin));

        selectedPolygon->vertexes = tmpVertexes;
        vector<Segment> tmpSegments;
        for (Segment &segment : orignalSegments)
            tmpSegments.push_back(Segment(Point(segment.b + (cursorPoint - origin)), Point(segment.e + (cursorPoint - origin))));

        selectedPolygon->segments = tmpSegments;
    }

    void finishEditing()
    {
        movingStarted = false;
        currentMode = DRAWING;
    }
};