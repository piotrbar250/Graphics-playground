#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"
#include "Polygon.hpp"
#include "Render.hpp"
#include "PolygonDrawer.hpp"

class VerticalRelationEditor
{
public:
    Render &render;
    VerticalRelationEditor(Render &render) : render(render) {}

    bool checkSegment(const Segment& segment)
    {
        return !segment.relation1 or (segment.b.x == segment.e.x);
    }

    void adjustSegment(Segment& segment)
    {
        segment.e =  {segment.b.x, segment.b.y + segment.len()};
    }

    void adjustPolygon(Polygon* polygon)
    {
        // vector<Segment> tmpSegments;
        // vector<Point> tmpVertexes;

        // for(int i = 0; i < polygon->segments.size(); i++)
        // {
        //     Segment& segment = polygon->segments[i];
        //     if(!checkSegment(segment))
        //     {
        //         cout << "wtf" << endl;
        //         adjustSegment(segment);
                
        //         tmpSegments.push_back(segment);
        //         tmpVertexes.push_back(segment.b);

        //         if(i + 1 < polygon->segments.size())
        //         {
        //             Segment& segment2 = polygon->segments[i+1];
        //             segment2.b = tmpSegments[i++].e;
        //             tmpSegments.push_back(segment);
        //         }
        //     }
        //     else
        //     {
        //         tmpSegments.push_back(segment);
        //         // if(!(tmpVertexes.back() == segment.b))
        //         //     tmpVertexes.pop_back();
        //         tmpVertexes.push_back(segment.b);
        //         // tmpVertexes.push_back(segment.e);
        //     }
        // }
        // polygon->segments = tmpSegments;
        // polygon->vertexes = tmpVertexes;

        for(int i = 0; i < polygon->segments.size(); i++)
        {
            Segment& segment = polygon->segments[i];
            if(i > 0 and !(segment.b == polygon->segments[i-1].e))
            {
                segment.b = polygon->segments[i-1].e;
            }
            polygon->vertexes[i] = segment.b;
            if(!checkSegment(segment))
            {
                adjustSegment(segment);
            }
        }

        if(!(polygon->segments[polygon->segments.size()-1].e == polygon->segments[0].b))
        {
            polygon->segments[0].b = polygon->segments[polygon->segments.size()-1].e;
            polygon->vertexes[0] = polygon->segments[0].b;
        }
    }

    void adjustPlain(PolygonDrawer& polygonDrawer)
    {
        for(Polygon*& polygon: render.polygons)
        {
            if(polygonDrawer.drawingStarted)
                continue;
            adjustPolygon(polygon);
        }
    }
};

/*

    void adjustPolygon(Polygon* polygon)
    {
        vector<Segment> tmpSegments;
        vector<Point> tmpVertexes;

        for(int i = 0; i < polygon->segments.size(); i++)
        {
            Segment& segment = polygon->segments[i];
            if(!checkSegment(segment))
            {
                cout << "wtf" << endl;
                adjustSegment(segment);
                
                tmpSegments.push_back(segment);
                tmpVertexes.push_back(segment.b);

                if(i + 1 < polygon->segments.size())
                {
                    segment = polygon->segments[i+1];
                    segment.b = tmpSegments[i++].e;
                    tmpSegments.push_back(segment);
                }
            }
            else
            {
                tmpSegments.push_back(segment);
                // if(!(tmpVertexes.back() == segment.b))
                //     tmpVertexes.pop_back();
                tmpVertexes.push_back(segment.b);
                // tmpVertexes.push_back(segment.e);
            }
        }
        polygon->segments = tmpSegments;
        polygon->vertexes = tmpVertexes;
    }
*/