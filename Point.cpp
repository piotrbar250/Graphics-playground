#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Point.hpp"
#include "Line.hpp"
#include "Polygon.hpp"

Point::Point() {}
// Point(float x, float y) : x(x), y(y) {}
Point::Point(float x, float y)
{
    this->x = x;
    this->y = y;
}

Point Point::transform(const Point &v)
{
    return Point(x + v.x, y + v.y);
}

// float Point::dot(const Point &v)
// {
//     return x * v.x + y * v.y;
// }

float Point::det(const Point &v) const
{
    return x*v.y - v.x*y;
}

float Point::norm()
{
    return sqrt(x * x + y * y);
}
Point Point::normalised()
{
    return Point(x / norm(), y / norm());
}

Point dtc(const Point &p)
{
    return Point(p.x, N - p.y);
}

Point Point::ctd(const Point &p)
{
    return Point(p.x, N - p.y);
}

ostream &operator<<(ostream &os, const Point &p)
{
    return os << p.x << ' ' << p.y;
}

Point Point::operator*(float len)
{
    return Point(x * len, y * len);
}

Point Point::operator+(const Point &p) const
{
    return Point(x + p.x, y + p.y);
}

Point Point::operator-(const Point &p) const
{
    return Point(x - p.x, y - p.y);
}

bool Point::operator==(const Point &p)
{
    return x == p.x and y == p.y;
}

bool Point::pointInCircle(const Point &p)
{
    if (sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y)) < radius)
        return true;
    return false;
}

bool Point::pointOnLine(const Line &l) const
{
    float dis = l.dis(*this);
    cout << endl << "dystans " << dis << " " << endl;
    if (dis >= eps)
        return false;
    if (min(l.segment.b.x, l.segment.e.x) > x + eps or x - eps > max(l.segment.b.x, l.segment.e.x))
        return false;
    if (min(l.segment.b.y, l.segment.e.y) > y + eps or y - eps >  max(l.segment.b.y, l.segment.e.y))
        return false;
    return true;
}

bool Point::pointInPolygon(const Polygon *polygon)
{
    return false;
}

void Point::drawCircle()
{
    CircleShape circle(radius);
    circle.setPosition(Vector2f(ctd(*this).x - radius, ctd(*this).y - radius));
    window.draw(circle);
}

// class Segment
// {
// public:
//     Point b, e;

//     Segment(const Point &b, const Point &e) : b(b.x, b.y), e(e.x, e.y)
//     {
//     }

//     bool operator==(const Segment &p)
//     {
//         return b == p.b and e == p.e;
//     }
// };