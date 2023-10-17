#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Point.cpp"
#include "Line.cpp"

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

class Polygon
{
public:
    vector<Point> vertices;
    Polygon()
    {

    }
};



int main()
{
    sf::RenderWindow window(sf::VideoMode(1152, 720), "Polygon editor");

    Vertex nodes[20];
    int n;

    bool segmentOn = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                cout << "hello" << endl;
                // nodes[n++] = Vertex(Vector2f(event.mouseButton.x, event.mouseButton.y));
                nodes[0] = Vertex(Vector2f(event.mouseButton.x, event.mouseButton.y));
                segmentOn = true;
                


                // if(!segmentOn)
                //     segmentOn = true;
                // else
                // {
                //     segmentOn = false;

                // }
            }
        }

        window.clear();

        if(segmentOn)
        {
            nodes[1] = Vector2f(Mouse::getPosition(window));
            cout << nodes[1].position.x << " " << nodes[1].position.y << " dis: ";
            
            float x1 = nodes[0].position.x;
            float y1 = nodes[0].position.y;

            float x2 = nodes[1].position.x;
            float y2 = nodes[1].position.y;

            float len = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
            float angle_rad = atan2(y1-y2, x2-x1);
            float angle_deg = angle_rad * 180.0 / M_PI;

            RectangleShape segment(Vector2f(len, 5));
            segment.setPosition(Vector2f(x1, y1));
            segment.rotate(-angle_deg);
            segment.setFillColor(Color(235, 222, 52));
            window.draw(segment);

            Line l({x1, y1}, {x2, y2});
            Vertex* nodes = l.vertexesOnLine();
            window.draw(nodes, M, sf::Points);

            Line l2(Point(x1, y1).transform(l.verticalVector*5), Point(x2, y2).transform(l.verticalVector*5));
            nodes = l2.vertexesOnLine();
            window.draw(nodes, M, sf::Points);


            Line l3(Point(x1, y1).transform(l.verticalVector*2.5), Point(x2, y2).transform(l.verticalVector*2.5));
            nodes = l3.vertexesOnLine();
            window.draw(nodes, M, sf::Points);
        
            Point pt(500, 200);

            cout << l.dis({100, 100}) << endl;
        }   

        window.display();
    }
}