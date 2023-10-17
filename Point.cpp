#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
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

    friend ostream& operator <<(ostream& os, const Point& p)
    {
        return os << p.x << ' ' << p.y;
    }

    Point operator*(float len)
    {
        return Point(x*len, y*len);
    }
};