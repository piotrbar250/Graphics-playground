#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Line.cpp"
#include "Polygon.cpp"
#include "global.hpp"

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




class Render
{
public:
    
    vector<Point> allVertexes;
    vector<Segment> allSegments;
    Render() : allVertexes(vector<Point>()), allSegments(vector<Segment>()) {}

    void drawPoint(const Point& p)
    {
        Vertex v(Vector2f(ctd(p).x, ctd(p).y));
        Vertex vA[] = {v};
        window.draw(vA, 1, Points);
        cout << "hello even here" << endl;
    }

    void drawSegment(const Segment& seg)
    {

    }
    
    void drawCircle(const Point& p)
    {
        CircleShape circle(radius);
        circle.setPosition(Vector2f(ctd(p).x-radius, ctd(p).y-radius));
        window.draw(circle);
    }

    void draw()
    {
        // for(auto v: allVertexes)
        //     draw(allVer)
    }

    void addVertex(const Point& p)
    {
        allVertexes.push_back({p.x, p.y});
    }

    void addSegment(const Point& b, const Point& e)
    {
        Segment seg({b.x, b.y}, {e.x, e.y});
        // allSegments.push_back(({b.x, b.y}, {e.x, e.y})); ?? why
        allSegments.push_back(seg);
    }
};

int main()
{
    window.create(sf::VideoMode(1152, 720), "Polygon editor");
    Render render;
    
    // int M = 1152, N = 720;
    Vertex nodes[20];
    int n;

    bool segmentOn = false;
    bool polygonStarted = false;
    Polygon* polygon;
    Point* prevPoint;

    window.display();
    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            
            if(event.type == Event::Closed)
                window.close();
            if(event.type == Event::MouseButtonPressed)
            {
                if(!polygonStarted)
                {
                    cout << "hello" << endl;
                    cout << window.getSize().x << " " << window.getSize().y << endl;
                    polygonStarted = true;
                    Point cursorPoint(ctd(Point(event.mouseButton.x, event.mouseButton.y)));
                    // polygon(cursorPoint);
                    polygon = new Polygon(cursorPoint);
                    cout << "cordy: " << cursorPoint.x << " " << cursorPoint.y << endl;
                }
            }
        }
       
        window.clear();
    
        window.display();
    }


    // while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //         if (event.type == sf::Event::MouseButtonPressed)
    //         {
    //             cout << "hello" << endl;
    //             // nodes[n++] = Vertex(Vector2f(event.mouseButton.x, event.mouseButton.y));
    //             nodes[0] = Vertex(Vector2f(event.mouseButton.x, event.mouseButton.y));
    //             segmentOn = true;
                


    //             // if(!segmentOn)
    //             //     segmentOn = true;
    //             // else
    //             // {
    //             //     segmentOn = false;

    //             // }
    //         }
    //     }

    //     window.clear();

    //     if(segmentOn)
    //     {
    //         nodes[1] = Vector2f(Mouse::getPosition(window));
    //         cout << nodes[1].position.x << " " << nodes[1].position.y << " dis: ";
            
    //         float x1 = nodes[0].position.x;
    //         float y1 = nodes[0].position.y;

    //         float x2 = nodes[1].position.x;
    //         float y2 = nodes[1].position.y;

    //         float len = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    //         float angle_rad = atan2(y1-y2, x2-x1);
    //         float angle_deg = angle_rad * 180.0 / M_PI;

    //         RectangleShape segment(Vector2f(len, 5));
    //         segment.setPosition(Vector2f(x1, y1));
    //         segment.rotate(-angle_deg);
    //         segment.setFillColor(Color(235, 222, 52));
    //         window.draw(segment);

    //         Line l({x1, y1}, {x2, y2});
    //         Vertex* nodes = l.vertexesOnLine();
    //         window.draw(nodes, M, sf::Points);

    //         Line l2(Point(x1, y1).transform(l.verticalVector*5), Point(x2, y2).transform(l.verticalVector*5));
    //         nodes = l2.vertexesOnLine();
    //         window.draw(nodes, M, sf::Points);


    //         Line l3(Point(x1, y1).transform(l.verticalVector*2.5), Point(x2, y2).transform(l.verticalVector*2.5));
    //         nodes = l3.vertexesOnLine();    
    //         window.draw(nodes, M, sf::Points);
        
    //         Point pt(500, 200);

    //         cout << l.dis({100, 100}) << endl;
    //     }   

    //     window.display();
    // }
}