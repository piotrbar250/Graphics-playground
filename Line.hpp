#pragma once
#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include <chrono>
#include <thread>
using namespace std;
using namespace sf;

class Point;
class Segment;

class Line
{
public:
    float A, B, C;
    bool isVertical;
    Point verticalVector;
    Segment segment;

    Line(const Point& a, const Point& b);

    float getY(float x) const;
    Vertex* vertexesOnLine() const;
    void draw() const;
    float dis(const Point& p) const;
    Line parallelLine(float offset);
};


/*
        A = p1.y - p2.y;
        B = p2.x - p1.x;
        C = p1.x * (p2.y - p1.y) + (p1.x - p2.x) * p1.y; 
        isVertical = B == 0;

        verticalVector = Point(A, B).normalised();
*/