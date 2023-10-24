#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Point.hpp"
#include "Polygon.hpp"
#include "global.hpp"
#include "Line.hpp"
#include "Button.hpp"
#include "BresenhamDrawingLineAlgorithm.hpp"
#include "NaiveDrawingLineAlgorithm.hpp"
using namespace std;
using namespace sf;

class Render
{
public:
    vector<Polygon*> polygons;
    vector<Line> lines;
    vector<Button> buttons;

    vector<Point> tmpVertexes;
    vector<Segment> tmpSegments;

    vector<VertexArray> sectors;

    Render() : polygons(vector<Polygon*>()) {}

    void drawPoint(const Point& p)
    {
        Vertex v(Vector2f(dtc(p).x, dtc(p).y));
        Vertex vA[] = {v};
        window.draw(vA, 1, Points);
    }

    void drawSegment(const Segment& seg)
    {
        if(currentAlgorithm == BRESENHAM)
        {
            BresenhamDrawingLineAlgorithm::drawLine(seg.b, seg.e, thickness);
            return;
        }

        float x1 = seg.b.x;
        float y1 = seg.b.y;

        float x2 = seg.e.x;
        float y2 = seg.e.y;

        float len = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
        float angle_rad = atan2(y1-y2, x2-x1);
        float angle_deg = angle_rad * 180 / M_PI;

        RectangleShape rect(Vector2f(len, thickness));
        rect.setPosition(Vector2f(dtc(seg.b).x, dtc(seg.b).y));
        rect.rotate(angle_deg);

        rect.setFillColor(Color::Green);

        RectangleShape rect2(Vector2f(len, thickness*5));
        rect2.setPosition(Vector2f(dtc(seg.b).x, dtc(seg.b).y));
        rect2.rotate(angle_deg);

        rect2.setFillColor(Color::White);

        window.draw(rect2);
        window.draw(rect);
    }
    
    void drawCircle(const Point& p)
    {
        CircleShape circle(radius);
        circle.setFillColor(Color::Blue);
        circle.setPosition(Vector2f(dtc(p).x-radius, dtc(p).y-radius));
        window.draw(circle);
    }

    void drawButton(const Button& button)
    {
        button.draw();
    }

    void drawLine(const Line& line)
    {
        line.draw();
    }

    void draw()
    {

        for(auto& sector: sectors)
            window.draw(sector);

        int i = 0;
        for(auto& polygon: polygons)
        {
            for(auto& seg: polygon->segments)
            drawSegment(seg);

            for(auto& p: polygon->vertexes)
            drawCircle(p);
        }

        for(Button& button: buttons)
        {
            button.draw();
        }
        buttons.clear();
        
        // for(auto& p: tmpVertexes)
        //     drawCircle(p);
        // for(auto& l: lines)
        // {
        //     drawLine(l);
        // }

        for(auto& s: tmpSegments)
            drawSegment(s);
            
    }

    void addPolygon(Polygon* polygon)
    {
        polygons.push_back(polygon);
    }
};
