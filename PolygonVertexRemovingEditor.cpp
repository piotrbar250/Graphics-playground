#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"
#include "Polygon.cpp"
#include "Render.cpp"

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

            cout << "sasiedzi " << *adjacentSegmentsPoints[0] << " " << *adjacentSegmentsPoints[1] << endl;

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