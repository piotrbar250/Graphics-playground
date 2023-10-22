#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"
#include "Polygon.cpp"
#include "Render.cpp"
#include "Line.cpp"

using namespace std;
using namespace sf;

class PolygonVertexInsertingEditor
{
public:
    Render &render;
    Polygon *selectedPolygon = nullptr;

    PolygonVertexInsertingEditor(Render &render) : render(render)
    {
        for (Polygon *&polygon : render.polygons)
        {
            for(Segment &segment: polygon->segments)
            {
                // cout << "hehjj" << endl;
                Line l(segment.b, segment.e);
                cout << "oryginalna " << " " << l.A << " " << l.B << " " << l.C << endl;
                // render.lines.push_back(l);
                render.lines.push_back(l.parallelLine(segment, thickness/2));
            }
        }
    }

    void mouseClickHandler(const Point& cursorPoint)
    {
        for (Polygon *&polygon : render.polygons)
        {
            for(Segment &segment: polygon->segments)
            {

            }
        }
    }
};