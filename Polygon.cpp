#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Point.cpp"
#include "global.hpp"
using namespace std;
using namespace sf;

class Polygon
{
public:
    vector<Point> vertices;
    Point start;
    
    Polygon() {}

    Polygon(Point& p) : start(p.x, p.y)
    {
        vertices.push_back(Point(p.x, p.y)); // is it needed?
        cout << "hello here" << endl;
        cout << window.getSize().x << " " << window.getSize().y << endl;
        p.drawCircle();
        
    }

    void addVertex(Point & p)
    {
        vertices.push_back(Point(p.x, p.y));
    }
};