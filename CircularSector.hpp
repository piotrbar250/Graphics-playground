#pragma once
#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include "global.hpp"
#include "Render.hpp"
#include <cmath>

float magnitude(const Point &v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

float dotProduct(const Point &a, const Point &b)
{
    return a.x * b.x + a.y * b.y;
}

bool isRightTurn(const Segment& segment1, const Segment& segment2) {
    Point dir1 = {segment1.e.x - segment1.b.x, segment1.e.y - segment1.b.y};
    Point dir2 = {segment2.e.x - segment2.b.x, segment2.e.y - segment2.b.y};

    float crossProduct = dir1.x * dir2.y - dir1.y * dir2.x;

    return crossProduct < 0;
}

float angleABC(const Point &A, const Point &B, const Point &C)
{
    Point BA = {A.x - B.x, A.y - B.y};
    Point BC = {C.x - B.x, C.y - B.y};

    float dot = dotProduct(BA, BC);
    float magBA = magnitude(BA);
    float magBC = magnitude(BC);

    float cosTheta = dot / (magBA * magBC);

    return std::acos(cosTheta);
}

float clockwiseAngle(const Point& v, const Point& u) {
    float dotProduct = v.dot(u);
    float crossProduct = v.cross(u);

    float angle = std::acos(dotProduct / (v.magnitude() * u.magnitude()));

    float angleInDegrees = angle * 180.0 / M_PI;

    return (crossProduct < 0) ? angleInDegrees : 360.0 - angleInDegrees;
}

sf::VertexArray calculateCircularSector(float radius, float startAngle, float arcAngle, sf::Vector2f position) {
    const int points = 50;
    
    sf::VertexArray sector(sf::TriangleFan, points + 2);
    sector[0].position = position;

    for (int i = 1; i <= points + 1; ++i) {
        float theta = startAngle + arcAngle * (i - 1) / points;

        float x = position.x + radius * cos(theta);
        float y = position.y + radius * sin(theta);

        sector[i].position = sf::Vector2f(x, y);
        sector[i].color = Color::White;
    }
    
    return sector;
}

VertexArray createCircularSector(Segment segment1, Segment segment2, float local_thickness)
{
    local_thickness = offsetThickness;

    Point A = segment1.b;
    Point B = segment1.e;
    Point C = segment2.e;

    float angleRad = angleABC(A, B, C);
    float angleDeg = angleRad * (180.0f / M_PI);

    Point v(1,0);
    Point u = segment2.e - segment2.b;


    if(!isRightTurn(segment1,segment2))
        return calculateCircularSector(local_thickness, clockwiseAngle(v,u) * (3.14159265f / 180.f), (360-angleDeg) * (3.14159265f / 180.f), sf::Vector2f(B.x, N-B.y));
    return calculateCircularSector(local_thickness, clockwiseAngle(v,u) * (3.14159265f / 180.f), (angleDeg) * (3.14159265f / 180.f), sf::Vector2f(B.x, N-B.y));
}

void createCircularSectors(Render& render)
{
    render.sectors = vector<VertexArray>();
    for(Polygon*& polygon: render.polygons)
    {
        for(int i = 1; i < polygon->segments.size(); i++)
        {
            VertexArray sector = createCircularSector(polygon->segments[i-1], polygon->segments[i], thickness);
            if(sector.getVertexCount() != 0)
                render.sectors.push_back(sector);
        }
          VertexArray sector = createCircularSector(polygon->segments[polygon->segments.size()-1], polygon->segments[0], thickness);
        render.sectors.push_back(sector);

    }
}
