#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"
#include "Polygon.hpp"
#include "Render.hpp"
#include "Line.hpp"

using namespace std;
using namespace sf;

class PolygonVertexInsertingEditor
{
public:
    Render &render;
    Polygon *selectedPolygon = nullptr;
    Segment *selectedSegment = nullptr;

    PolygonVertexInsertingEditor(Render &render) : render(render)
    {
        for (Polygon *&polygon : render.polygons)
        {
            for(Segment &segment: polygon->segments)
            {
                // cout << "hehjj" << endl;
                Line l(segment.b, segment.e);
                Line parallel = l.parallelLine(thickness/2);
                cout << "oryginalna " << " " << l.A << " " << l.B << " " << l.C << endl;
                // render.lines.push_back(l);
                render.lines.push_back(parallel);
            }
        }
    }

    void mouseClickHandler(const Point& cursorPoint)
    {
        int i = 0;
        for (Polygon *&polygon : render.polygons)
        {
            int j = 0;
            for(Segment &segment: polygon->segments)
            {
                Line l(segment.b, segment.e);
                Line parallel = l.parallelLine(thickness/2);
            
                if(cursorPoint.pointOnLine(parallel))
                {
                    cout << endl << "yeah dla panow " << i << " " << j << endl;
                    selectedPolygon = polygon;
                    selectedSegment = &segment;
                }
                j++;
            }
            i++;
        }

        if(selectedSegment)
        {
            Point newVertex = cursorPoint;
            vector<Point> tmpVertexes;
            for(Point vertex: selectedPolygon->vertexes)
            {
                tmpVertexes.push_back(vertex);
                if(vertex == selectedSegment->b)
                    tmpVertexes.push_back(newVertex);
            }
            selectedPolygon->vertexes = tmpVertexes;


            vector<Segment> tmpSegments;
            for(Segment& segment: selectedPolygon->segments)
            {
                if (segment == *selectedSegment)
                {
                    tmpSegments.push_back({segment.b, newVertex});
                    tmpSegments.push_back({newVertex, segment.e});
                }
                else
                    tmpSegments.push_back(segment);
            }
            selectedPolygon->segments = tmpSegments;
        }

        currentMode = DRAWING;
    }

    ~PolygonVertexInsertingEditor()
    {
        selectedPolygon = nullptr;
        selectedSegment = nullptr;
    }
};