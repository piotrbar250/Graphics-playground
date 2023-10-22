#pragma once
#include <SFML/Graphics.hpp>
#include "Point.cpp"
#include <chrono>
#include <thread>
using namespace std;
using namespace sf;

class Line
{
public:
    float A, B, C;
    bool isVertical;
    Point verticalVector;

    Line(const Point& a, const Point& b)
    {
        A = b.y - a.y;
        B = a.x - b.x;
        C = -A * a.x - B * a.y;
        isVertical = B == 0;
        verticalVector = Point(b.y - a.y, a.x - b.x).normalised();

    //     cout << "Tworze prosta dla punktow " << endl;
    //     cout << a << " " << b << endl;
    //     cout << A << " " << B << " " << C << endl;
    //     cout << "wektor prostopadly: " << verticalVector << endl;
    }

    float getY(float x) const
    {
        return (-A*x - C) / B;
    }

    Vertex* vertexesOnLine() const
    {
        Vertex* nodes = new Vertex[M];
        if(!isVertical)
        {
            for(int i = 0; i < M; i++)
            {
                nodes[i].position = Vector2f(i, N-getY(i));
            }
        }
        return nodes;
    }

    void draw() const
    {
        Vertex* nodes = vertexesOnLine();
        window.draw(nodes, M, sf::Lines);
    }

    float dis(const Point& p)
    {
        return fabs(A*p.x + B*p.y + C) / sqrt(A*A + B*B);
    }

    Line parallelLine(const Segment& segment, float offset)
    {
        Line parallel(segment.b + verticalVector*offset, segment.e + verticalVector*offset);
    
        cout << "rownolegla " << parallel.A << " " << parallel.B << " " << parallel.C << endl;

        return parallel;
    }
};
/*
        A = p1.y - p2.y;
        B = p2.x - p1.x;
        C = p1.x * (p2.y - p1.y) + (p1.x - p2.x) * p1.y; 
        isVertical = B == 0;

        verticalVector = Point(A, B).normalised();
*/