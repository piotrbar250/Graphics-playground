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
    vector<Point> orignalVertexes;
    vector<Segment> orignalSegments;

    PolygonMovingEditor(Render &render) : render(render) {}

    void mouseClickHandler(const Point &cursorPoint)
    {
        if (!movingStarted)
        {
            // std::cout << "tu tylko na poczatku" << std::endl;
            movingStarted = true;
            render.tmpSegment = new Segment(cursorPoint, {M, cursorPoint.y});
            origin = cursorPoint;

            int cnt = 0;
            int i = 0;
            for (Polygon *&polygon : render.polygons)
            {
                int j = 0;
                for (Segment &segment : polygon->segments)
                {
                    if (segment.intersect(*render.tmpSegment))
                    {
                        cnt++;
                        // cout << "o tak " << i << " " << j << endl;
                    }
                    j++;
                }
                if (cnt % 2 == 1)
                {
                    selectedPolygon = polygon;
                    orignalVertexes = polygon->vertexes;
                    orignalSegments = polygon->segments;
                    break;
                }
                i++;
            }
            if(!selectedPolygon)
            {
                movingStarted = false;
                currentMode = DRAWING;
            }
        }
        else
        {
            Point cursorPoint(dtc(Point(Mouse::getPosition(window).x, Mouse::getPosition(window).y)));

            vector<Point> tmpVertexes;
            for(Point& vertex: orignalVertexes)
            {
                tmpVertexes.push_back(vertex + (cursorPoint - origin));
                // tmpVertexes.push_back(vertex*2);
            }
            selectedPolygon->vertexes = tmpVertexes;
            vector<Segment> tmpSegments;
            for(Segment& segment: orignalSegments)
            {
                tmpSegments.push_back(Segment(Point(segment.b+(cursorPoint - origin)), Point(segment.e+(cursorPoint - origin))));
            }
            selectedPolygon->segments = tmpSegments;

            movingStarted = false;
            currentMode = DRAWING;
        }
    }

    void temporaryPolygonHandler()
    {
        if(movingStarted)
        {
            // cout << "co jest" << endl;
            Point cursorPoint(dtc(Point(Mouse::getPosition(window).x, Mouse::getPosition(window).y)));

            vector<Point> tmpVertexes;
            for(Point& vertex: orignalVertexes)
            {
                tmpVertexes.push_back(vertex + (cursorPoint - origin));
                // tmpVertexes.push_back(vertex*2);
            }
            selectedPolygon->vertexes = tmpVertexes;
            vector<Segment> tmpSegments;
            for(Segment& segment: orignalSegments)
            {
                tmpSegments.push_back(Segment(Point(segment.b+(cursorPoint - origin)), Point(segment.e+(cursorPoint - origin))));
            }
            selectedPolygon->segments = tmpSegments;
        }
    }
};