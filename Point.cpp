#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"
using namespace std;
using namespace sf;


class Point
{
public:
    float x, y;
    Point(){}
    // Point(float x, float y) : x(x), y(y) {}
    Point(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    Point transform(const Point& v)
    {
        return Point(x+v.x, y+v.y);
    }

    float dot(const Point& v)
    {
        return x*v.x + y*v.y;
    }

    float norm()
    {
        return sqrt(x*x + y*y);
    }
    Point normalised()
    {
        return Point(x / norm(), y / norm());
    }

    friend Point dtc(const Point& p)
    {
        return Point(p.x, N - p.y);
    }

    friend Point ctd(const Point& p)
    {
        return Point(p.x, N - p.y);
    }

    friend ostream& operator <<(ostream& os, const Point& p)
    {
        return os << p.x << ' ' << p.y;
    }

    Point operator*(float len)
    {
        return Point(x*len, y*len);
    }

    bool pointInCircle(const Point& p)
    {
        if(sqrt((p.x-x)*(p.x-x) + (p.y-y)*(p.y-y)) < radius)
            return true;
        return false;
    }

    bool operator==(const Point& p)
    {
        return x == p.x and y == p.y;
    }

    // void drawPoint()
    // {
    //     Vertex v(Vector2f(ctd(*this).x, ctd(*this).y));
    //     Vertex vA[] = {v};
    //     window.draw(vA, 1, Points);
    //     cout << "hello even here" << endl;
    // }

    void drawCircle()
    {
        CircleShape circle(radius);
        circle.setPosition(Vector2f(ctd(*this).x-radius, ctd(*this).y-radius));
        window.draw(circle);
    }
};

class Segment
{
public:
    Point b, e;

    Segment(const Point& b, const Point& e) : b(b.x, b.y), e(e.x, e.y)
    {}
};