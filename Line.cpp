#pragma once
#include <SFML/Graphics.hpp>
#include "Point.cpp"
using namespace std;
using namespace sf;

class Line
{
public:
    float A, B, C;
    bool isVertical;
    Point verticalVector;

    Line(const Point& p1, const Point& p2)
    {
        A = p1.y - p2.y;
        B = p2.x -p1.x;
        C = p1.x * (p2.y - p1.y) + (p1.x - p2.x) * p1.y; 
        isVertical = B == 0;
        verticalVector = Point(A, B).normalised();
    }

    float getY(float x)
    {
        return (-A*x - C) / B;
    }

    Vertex* vertexesOnLine()
    {
        Vertex* nodes = new Vertex[M];
        if(!isVertical)
        {
            for(int i = 0; i < M; i++)
                nodes[i].position = Vector2f(i, getY(i));
        }
        return nodes;
    }

    float dis(const Point& p)
    {
        return fabs(A*p.x + B*p.y + C) / sqrt(A*A + B*B);
    }
};