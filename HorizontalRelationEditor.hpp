#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"
#include "Polygon.hpp"
#include "Render.hpp"
#include "PolygonDrawer.hpp"

class HorizontalRelationEditor
{
public:
    Render &render;
    HorizontalRelationEditor(Render &render) : render(render) {}

    bool checkSegment(const Segment &segment)
    {
        return !segment.relation2 or (segment.b.y == segment.e.y);
    }

    void adjustSegment(Segment &segment)
    {
        segment.e = {segment.b.x + segment.len(), segment.b.y};
    }

    void adjustPolygon(Polygon *polygon)
    {
        for (int i = 0; i < polygon->segments.size(); i++)
        {
            Segment &segment = polygon->segments[i];
            if (i > 0 and !(segment.b == polygon->segments[i - 1].e))
            {
                segment.b = polygon->segments[i - 1].e;
            }
            polygon->vertexes[i] = segment.b;
            if (!checkSegment(segment))
            {
                adjustSegment(segment);
            }
        }

        if (!(polygon->segments[polygon->segments.size() - 1].e == polygon->segments[0].b))
        {
            polygon->segments[0].b = polygon->segments[polygon->segments.size() - 1].e;
            polygon->vertexes[0] = polygon->segments[0].b;
        }
    }

    void adjustPlain(PolygonDrawer &polygonDrawer)
    {
        for (Polygon *&polygon : render.polygons)
        {
            if (polygonDrawer.drawingStarted)
                continue;
            adjustPolygon(polygon);
        }
    }
};