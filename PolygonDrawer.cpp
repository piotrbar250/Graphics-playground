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
    Render &render;

    bool firstIterationAfterClicking = false;

    PolygonDrawer(Render &render) : render(render) {}
    void mouseClickHandler(const Point &cursorPoint)
    {
        firstIterationAfterClicking = true;

        if (!drawingStarted)
        {
            drawingStarted = true;
            polygon = new Polygon(cursorPoint);
            render.addPolygon(polygon);
            polygon->addVertex(cursorPoint);
            prevPoint = new Point(cursorPoint.x, cursorPoint.y);
        }
        else
        {
            polygon->popSegment();
            polygon->popVertex();

            if (polygon->start.pointInCircle(cursorPoint))
            {
                drawingStarted = false;

                polygon->addSegment(*prevPoint, polygon->start);
                delete prevPoint;

                cout << "Drawing has been finished" << endl;
                for (Segment &segment : polygon->segments)
                {
                    cout << segment.b << " " << segment.e << endl;
                }
                cout << endl;

                for (Point &vertex : polygon->vertexes)
                {
                    cout << vertex << endl;
                }
            }
            else
            {
                polygon->addSegment(*prevPoint, cursorPoint);
                delete prevPoint;
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

            if (firstIterationAfterClicking)
                firstIterationAfterClicking = false;
            else
            {
                polygon->popVertex();
                polygon->popSegment();
            }

            polygon->addVertex(cursorPoint);
            polygon->addSegment(*prevPoint, cursorPoint);
        }
    }
};

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

    void mouseClickHandler(const Point &cursorPoint)
    {
        if (!editingStarted)
        {
            editingStarted = true;
            for (Polygon *&polygon : render.polygons)
            {
                for (Point &vertex : polygon->vertexes)
                {
                    if (vertex.pointInCircle(cursorPoint))
                    {
                        cout << "yeahh" << endl;
                        selectedPoint = &vertex;
                        selectedPolygon = polygon;
                    }
                }
            }

            if (selectedPoint)
            {
                for (Segment &segment : selectedPolygon->segments)
                {
                    if (segment.b == *selectedPoint)
                    {

                        if (!adjacentSegments[0])
                        {
                            cout << "yeahh2" << endl;
                            adjacentSegments[0] = &segment;
                            adjacentSegmentsPoints[0] = &(segment.b);
                        }
                        else
                        {
                            cout << "yeahh3" << endl;
                            adjacentSegments[1] = &segment;
                            adjacentSegmentsPoints[1] = &(segment.b);
                            break;
                        }
                    }

                    if (segment.e == *selectedPoint)
                    {

                        if (!adjacentSegments[0])
                        {
                            cout << "yeahh4" << endl;
                            adjacentSegments[0] = &segment;
                            adjacentSegmentsPoints[0] = &(segment.e);
                        }
                        else
                        {
                            cout << "yeahh5" << endl;
                            adjacentSegments[1] = &segment;
                            adjacentSegmentsPoints[1] = &(segment.e);
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            editingStarted = false;
            Point cursorPoint(ctd(Point(Mouse::getPosition(window).x, Mouse::getPosition(window).y)));
            *(adjacentSegmentsPoints[0]) = cursorPoint;
            *(adjacentSegmentsPoints[1]) = cursorPoint;
            *selectedPoint = cursorPoint;
            currentMode = DRAWING;
        }
    }

    void temporarySegmentHanlder()
    {
        if (editingStarted)
        {
            Point cursorPoint(ctd(Point(Mouse::getPosition(window).x, Mouse::getPosition(window).y)));
            // delete adjacentSegmentsPoints[0];
            *(adjacentSegmentsPoints[0]) = cursorPoint;
            *(adjacentSegmentsPoints[1]) = cursorPoint;
            *selectedPoint = cursorPoint;
            // adjacentSegmentsPoints[1] = new Point(cursorPoint);
            // adjacentSegments[0]->b = new Point(cursorPoint);
            // adjacentSegmentsPoints[1]-> = new Point(cursorPoint);

            cout << *adjacentSegmentsPoints[0] << "    " << adjacentSegments[0]->b << " " << adjacentSegments[0]->e << endl;
        }
    }
};

class PolygonVertexRemovingEditor
{
public:
    Render &render;
    Polygon *selectedPolygon = nullptr;
    Point *selectedPoint = nullptr;
    Segment *adjacentSegments[2];
    Point *adjacentSegmentsPoints[2];

    PolygonVertexRemovingEditor(Render &render) : render(render) {}
    void mouseClickHandler(const Point &cursorPoint)
    {
        for (Polygon *&polygon : render.polygons)
        {
            for (Point &vertex : polygon->vertexes)
            {
                if (vertex.pointInCircle(cursorPoint))
                {
                    cout << "yeahh-removing" << endl;
                    selectedPoint = &vertex;
                    selectedPolygon = polygon;
                }
            }
        }

        if (selectedPoint)
        {
            for (Segment &segment : selectedPolygon->segments)
            {
                if (segment.b == *selectedPoint)
                {

                    if (!adjacentSegments[0])
                    {
                        cout << "yeahh2" << endl;
                        adjacentSegments[0] = &segment;
                        adjacentSegmentsPoints[0] = &(segment.e);
                    }
                    else
                    {
                        cout << "yeahh3" << endl;
                        adjacentSegments[1] = &segment;
                        adjacentSegmentsPoints[1] = &(segment.e);
                        break;
                    }
                }

                if (segment.e == *selectedPoint)
                {

                    if (!adjacentSegments[0])
                    {
                        cout << "yeahh4" << endl;
                        adjacentSegments[0] = &segment;
                        adjacentSegmentsPoints[0] = &(segment.b);
                    }
                    else
                    {
                        cout << "yeahh5" << endl;
                        adjacentSegments[1] = &segment;
                        adjacentSegmentsPoints[1] = &(segment.b);
                        break;
                    }
                }
            }

            vector<Segment> tmp = vector<Segment>(); // is that needed?
            int cnt = 0;

            cout << "sasiedzi " <<  *adjacentSegmentsPoints[0] << " " << *adjacentSegmentsPoints[1] << endl;

            for (Segment &segment : selectedPolygon->segments)
            {
                if (segment.b == *selectedPoint or segment.e == *selectedPoint && cnt == 0)
                {
                    cnt++;
                    tmp.push_back(Segment(*adjacentSegmentsPoints[0], *adjacentSegmentsPoints[1]));
                }
                else
                    tmp.push_back(segment);
            }
            selectedPolygon->segments = tmp;
        }
    }
};