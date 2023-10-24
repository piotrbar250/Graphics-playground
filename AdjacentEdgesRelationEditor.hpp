#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"
#include "Polygon.hpp"
#include "Render.hpp"
#include "PolygonDrawer.hpp"

class AdjacentEdgesRelationEditor
{
public:
    Render &render;
    AdjacentEdgesRelationEditor(Render &render) : render(render) {}

    bool checkSegment(const Segment &segment)
    {
        return !segment.relation2 or (segment.b.y == segment.e.y);
    }

    Segment& leftSegment(Polygon* polygon, int i)
    {
        if(i > 0)
            return polygon->segments[i-1];
        return polygon->segments[polygon->segments.size()-1];
    }
    Segment& rightSegment(Polygon* polygon, int i)
    {
        if(i + 1 < polygon->segments.size())
            return polygon->segments[i+1];
        return polygon->segments[0];
    }
    
    void adjustSegment(Polygon* polygon, int i)
    {
        Segment &segment = polygon->segments[i];
        Segment left = leftSegment(polygon, i);
        if(left.relation3)
        {
            if(left.isVertical() and segment.isVertical())
            {
                segment.e = segment.e + Point(20, 20);
            }
            else if(left.isHorizontal() and segment.isHorizontal())
            {
                segment.e = segment.e + Point(20, 20);
            }
        }
    }

    void adjustSegmentOpposite(Polygon* polygon, int i)
    {
        Segment &segment = polygon->segments[i];
        Segment left = leftSegment(polygon, i);
        if(left.relation3)
        {
            if(left.isVertical() and segment.isVertical())
            {
                segment.b = segment.b + Point(20, 20);
            }
            else if(left.isHorizontal() and segment.isHorizontal())
            {
                segment.b = segment.b + Point(20, 20);
            }
        }
    }

    void clockwiseProcedure(Polygon *polygon)
    {
        for (int i = 0; i < polygon->segments.size(); i++)
        {
            Segment &segment = polygon->segments[i];
            if (i > 0 and !(segment.b == polygon->segments[i - 1].e))
                segment.b = polygon->segments[i - 1].e;
            
            adjustSegment(polygon, i);

            polygon->vertexes[i] = segment.b;
        }

        if (!(polygon->segments[polygon->segments.size() - 1].e == polygon->segments[0].b))
        {
            polygon->segments[0].b = polygon->segments[polygon->segments.size() - 1].e;
            polygon->vertexes[0] = polygon->segments[0].b;
        }
    }    

    void counterclockwiseProcedure(Polygon *polygon)
    {
        for (int i = 0; i < polygon->segments.size(); i++)
        {
            Segment &segment = polygon->segments[i];
            if (i > 0 and !(segment.e == polygon->segments[i - 1].b))
            {
                segment.e = polygon->segments[i - 1].b;
            }
            
            adjustSegmentOpposite(polygon, i);

            polygon->vertexes[i] = segment.e;
        }

        if (!(polygon->segments[polygon->segments.size() - 1].b == polygon->segments[0].e))
        {
            polygon->segments[0].e = polygon->segments[polygon->segments.size() - 1].b;
            polygon->vertexes[0] = polygon->segments[0].e;
        }
    }

    void adjustPolygon(Polygon *polygon)
    {
        clockwiseProcedure(polygon);   

        reverse(polygon->segments.begin(), polygon->segments.end());
        reverse(polygon->vertexes.begin(), polygon->vertexes.end());

        counterclockwiseProcedure(polygon);

        reverse(polygon->segments.begin(), polygon->segments.end());
        reverse(polygon->vertexes.begin(), polygon->vertexes.end());
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

    void adjustRelations(PolygonDrawer &polygonDrawer)
    {
        if (polygonDrawer.drawingStarted)
                return;
        for (Polygon *&polygon : render.polygons)
        {
            for(int i = 0; i < polygon->segments.size(); i++)
            {
                Segment& segment = polygon->segments[i];
                Segment& left = leftSegment(polygon, i);
                Segment& right = rightSegment(polygon, i);
                if(segment.relation3 && segment.isVertical())
                {
                    left.relation1 = false;
                    right.relation1 = false;
                }
                if(segment.relation3 && segment.isHorizontal())
                {
                    left.relation2 = false;
                    right.relation2 = false;
                }
            }
        }
    }
};
