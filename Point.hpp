#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"

class Line;

using namespace std;
using namespace sf;


class Point
{
public:
    float x, y;
    Point();
    Point(float x, float y);

    Point transform(const Point& v);

    float dot(const Point& v);

    float norm();
    Point normalised();

    friend Point dtc(const Point& p);

    static Point ctd(const Point& p);

    friend ostream& operator <<(ostream& os, const Point& p);

    Point operator*(float len);
    
    Point operator+(const Point& p) const;

    bool pointInCircle(const Point& p);

    bool pointOnLine(const Line& l) const;

    bool operator==(const Point& p);


    void drawCircle();
};

class Segment
{
public:
    Point b, e;

    Segment(const Point& b, const Point& e) : b(b.x, b.y), e(e.x, e.y)
    {}

    bool operator ==(const Segment& p)
    {
        return b == p.b and e == p.e;
    }
};