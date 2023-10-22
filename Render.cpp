#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Point.cpp"
#include "Polygon.cpp"
#include "global.hpp"
#include "Line.cpp"
using namespace std;
using namespace sf;

class Render
{
public:
    vector<Polygon*> polygons;
    vector<Line> lines;

    Render() : polygons(vector<Polygon*>()) {}

    void drawPoint(const Point& p)
    {
        Vertex v(Vector2f(ctd(p).x, ctd(p).y));
        Vertex vA[] = {v};
        window.draw(vA, 1, Points);
    }

    void drawSegment(const Segment& seg)
    {
        float x1 = seg.b.x;
        float y1 = seg.b.y;

        float x2 = seg.e.x;
        float y2 = seg.e.y;

        float len = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
        float angle_rad = atan2(y1-y2, x2-x1);
        float angle_deg = angle_rad * 180 / M_PI;

        RectangleShape rect(Vector2f(len, thickness));
        rect.setPosition(Vector2f(ctd(seg.b).x, ctd(seg.b).y));
        rect.rotate(angle_deg);
        rect.setFillColor(Color::Green);
        window.draw(rect);
    }
    
    void drawCircle(const Point& p)
    {
        CircleShape circle(radius);
        circle.setPosition(Vector2f(ctd(p).x-radius, ctd(p).y-radius));
        window.draw(circle);
    }

    void drawLine(const Line& line)
    {
        line.draw();
    }

    void draw()
    {
        int i = 0;
        for(auto& polygon: polygons)
        {
            for(auto& seg: polygon->segments)
            drawSegment(seg);

            for(auto& p: polygon->vertexes)
            drawCircle(p);
        }

        for(auto& l: lines)
        {
            drawLine(l);
        }
    }

    void addPolygon(Polygon* polygon)
    {
        polygons.push_back(polygon);
    }
};
