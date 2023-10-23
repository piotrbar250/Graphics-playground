#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"

class Line;
class Polygon;
class Button;

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
    float det(const Point& v) const;

    float norm();
    Point normalised();

    friend Point dtc(const Point& p);

    static Point ctd(const Point& p);

    friend ostream& operator <<(ostream& os, const Point& p);

    Point operator*(float len);
    
    Point operator+(const Point& p) const;

    Point operator-(const Point& p) const;

    bool operator==(const Point& p);

    bool vectorIntersection(const Point& p) const;

    bool pointInCircle(const Point& p);

    bool pointOnLine(const Line& l) const;

    bool pointInPolygon(const Polygon* polygon);

    void drawCircle();
};

class Segment
{
public:
    Point b, e;
    bool relation1 = false; // poziomoa
    bool relation2 = false; // pionowa
    bool relation3 = false; // przylegle
    Button* button1 = nullptr; // pozioma
    Button* button2 = nullptr; // pionowa    
    Button* button3 = nullptr; // przylegle    


    Segment() {}
    Segment(const Point& b, const Point& e) : b(b.x, b.y), e(e.x, e.y)
    {}

    bool operator ==(const Segment& p)
    {
        return b == p.b and e == p.e;
    }

    bool intersect(const Segment& s)
    {
        Point ab = e - b;
        Point v1 = s.b - b;
        Point v2 = s.e - b;
        if(ab.det(v1) * ab.det(v2) >= 0)
            return false;
        
        ab = s.e - s.b;
        v1 = b - s.b;
        v2 = e - s.b;
        if(ab.det(v1) * ab.det(v2) >= 0)
            return false;
        return true;
    }

    Point middle()
    {
        Point ab = (e - b) * (0.5);
        return b + ab;
    }

    float len() const
    {
        Point ab = e - b;
        return sqrt(ab.x * ab.x + ab.y * ab.y);
    }
};