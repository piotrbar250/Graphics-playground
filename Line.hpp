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
    bool above(const Point& p) const;
};
