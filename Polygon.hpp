#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Point.hpp"
#include "Button.hpp"
#include "global.hpp"
using namespace std;
using namespace sf;

class Polygon
{
public:
    vector<Point> vertexes;
    vector<Segment> segments;
    
    Point start;

    Polygon() : vertexes(vector<Point>()), segments(vector<Segment>()) {}

    Polygon(const Point& p) : start(p.x, p.y)
    {
        // vertexes.push_back(Point(p.x, p.y)); // is it needed?
    }

    void addVertex(const Point & p)
    {
        vertexes.push_back(Point(p.x, p.y));
    }

    void addSegment(const Point& b, const Point& e)
    {
        Segment seg({b.x, b.y}, {e.x, e.y});
        // segments.push_back(({b.x, b.y}, {e.x, e.y})); ?? why
        segments.push_back(seg);
    }

    void popVertex()
    {
        vertexes.pop_back();
    }

    void popSegment()
    {
        segments.pop_back();
    }
};