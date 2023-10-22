#include <SFML/Graphics.hpp>
#include "Line.hpp"

#include <chrono>
#include <thread>
using namespace std;
using namespace sf;

Line::Line(const Point &a, const Point &b) : segment(a, b)
{
    A = b.y - a.y;
    B = a.x - b.x;
    C = -A * a.x - B * a.y;

    // segment = Segment(a, b);
    isVertical = B == 0;
    verticalVector = Point(b.y - a.y, a.x - b.x).normalised();
    //     cout << "Tworze prosta dla punktow " << endl;
    //     cout << a << " " << b << endl;
    //     cout << A << " " << B << " " << C << endl;
    //     cout << "wektor prostopadly: " << verticalVector << endl;
}

float Line::getY(float x) const
{
    return (-A * x - C) / B;
}

Vertex* Line::vertexesOnLine() const
{
    Vertex *nodes = new Vertex[M];
    if (!isVertical)
    {
        for (int i = 0; i < M; i++)
        {
            nodes[i].position = Vector2f(i, N - getY(i));
        }
    }
    return nodes;
}

void Line::draw() const
{
    Vertex *nodes = vertexesOnLine();
    window.draw(nodes, M, sf::Lines);
    delete nodes;
}

float Line::dis(const Point &p) const
{
    return fabs(A * p.x + B * p.y + C) / sqrt(A * A + B * B);
}

Line Line::parallelLine(float offset)
{
    Line parallel(segment.b + verticalVector * offset, segment.e + verticalVector * offset);

    cout << "rownolegla " << parallel.A << " " << parallel.B << " " << parallel.C << endl;

    return parallel;
}