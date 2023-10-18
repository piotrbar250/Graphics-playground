#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "global.hpp"
#include "Line.cpp"
#include "Polygon.cpp"
#include "Render.cpp"

using namespace std;
using namespace sf;


Vertex dtc(const Vertex& p)
{
    return Vertex(Vector2f(p.position.x, N - p.position.y));
}

Vertex ctd(const Vertex& p)
{
    return Vertex(Vector2f(p.position.x, N - p.position.y));
}

ostream& operator <<(ostream& os, const Vertex& v)
{
    return os << v.position.x << " " << v.position.y;
}

RenderWindow window;

int main()
{
    window.create(sf::VideoMode(1152, 720), "Polygon editor");
    window.display();

    Render render;

    bool polygonStarted = false;
    Polygon* polygon;
    Point* prevPoint;

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {   
            if(event.type == Event::Closed)
                window.close();
            if(event.type == Event::MouseButtonPressed)
            {
                Point cursorPoint(ctd(Point(event.mouseButton.x, event.mouseButton.y)));

                if(!polygonStarted)
                {
                    polygon = new Polygon(cursorPoint);
                    render.addPolygon(polygon);
                    polygonStarted = true;
                    
                    prevPoint = new Point(cursorPoint.x, cursorPoint.y);
                    cout << "cordy: " << cursorPoint.x << " " << cursorPoint.y << endl;
                }
                else
                {
                    polygon->addSegment(*prevPoint, cursorPoint);
                    delete prevPoint;
                
                    if(polygon->start.pointInCircle(cursorPoint))
                    {
                        polygonStarted = false;
                        polygon->popVertex();
                    }
                    else
                    {
                        polygon->addVertex(cursorPoint);
                        prevPoint = new Point(cursorPoint.x, cursorPoint.y);
                    }
                }
            }
        }

        if(polygonStarted)
        {
            Point cursorPoint(ctd(Point(Mouse::getPosition(window).x, Mouse::getPosition(window).y)));;
            cout << "cordy2: " << cursorPoint.x << " " << cursorPoint.y << endl;

            if(polygon->vertexes.size() > 1)
                polygon->popVertex();
            if(polygon->segments.size() > 0)
                polygon->popSegment();

            polygon->addVertex(cursorPoint);
            polygon->addSegment(*prevPoint, cursorPoint);
        }
        else
        {
            cout << "yeahh "; //polygon->vertexes.size() <<  endl;
            if(polygon != nullptr)
            {
                cout << polygon->vertexes.size() << " " << polygon->segments.size() << endl;
            }
            else
                cout << endl;
        }
       
        window.clear();

        render.draw();

        window.display();
    }
}