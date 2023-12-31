#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"
#include "Polygon.hpp"
#include "Render.hpp"

using namespace std;
using namespace sf;


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
                    // cout << "yeahh-removing" << endl;
                    selectedPoint = &vertex;
                    selectedPolygon = polygon;
                }
            }
        }

        if (selectedPoint)
        {
            // cout << "Removing is started" << endl;
            printPolygon();
            for (Segment &segment : selectedPolygon->segments)
            {
                if (segment.b == *selectedPoint)
                {
                    if (!adjacentSegments[0])
                    {
                        adjacentSegments[0] = &segment;
                        adjacentSegmentsPoints[0] = &(segment.e);
                    }
                    else
                    {
                        adjacentSegments[1] = &segment;
                        adjacentSegmentsPoints[1] = &(segment.e);
                        break;
                    }
                }

                if (segment.e == *selectedPoint)
                {

                    if (!adjacentSegments[0])
                    {
                        adjacentSegments[0] = &segment;
                        adjacentSegmentsPoints[0] = &(segment.b);
                    }
                    else
                    {
                        adjacentSegments[1] = &segment;
                        adjacentSegmentsPoints[1] = &(segment.b);
                        break;
                    }
                }
            }

            vector<Segment> tmp = vector<Segment>(); // is that needed? - NO
            int cnt = 0;

            // cout << "sasiedzi " << *adjacentSegmentsPoints[0] << " " << *adjacentSegmentsPoints[1] << endl;

            int loopCnt = 0;
            for (Segment &segment : selectedPolygon->segments)
            {
                if (segment.b == *selectedPoint or segment.e == *selectedPoint)
                {
                    // cout << "usuwam segment " << segment.b << " " << segment.e << endl;
                    if(cnt++ == 0)
                    {
                        if(loopCnt == 0 && segment.b == *selectedPoint)
                            tmp.push_back(Segment(*adjacentSegmentsPoints[1], *adjacentSegmentsPoints[0]));
                        else
                            tmp.push_back(Segment(*adjacentSegmentsPoints[0], *adjacentSegmentsPoints[1]));
                    }
                }
                else
                    tmp.push_back(segment);

                loopCnt++;
            }
            selectedPolygon->segments = tmp;


            // vector<Point> tmpP;
            // for(Point& vertex: selectedPolygon->vertexes)
            // {
            //     if(vertex == *selectedPoint)
            //         continue;
            //     tmpP.push_back(vertex);
            // }
            // selectedPolygon->vertexes = tmpP;

            vector<Point> tmpP;
            for(Segment& segment: selectedPolygon->segments)
            {
                tmpP.push_back(segment.b);
            }
            selectedPolygon->vertexes = tmpP;

            // cout << "Removing has been finished" << endl;
            printPolygon();
        }

        currentMode = DRAWING;
    }

    void printPolygon()
    {
        // for (Segment &segment : selectedPolygon->segments)
        //     cout << segment.b << " " << segment.e << endl;
        // cout << endl;
        // for (Point &vertex : selectedPolygon->vertexes)
        //     cout << vertex << endl;
    }
};