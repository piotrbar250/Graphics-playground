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
    // Calculate direction vectors for the segments
    Point dir1 = {segment1.e.x - segment1.b.x, segment1.e.y - segment1.b.y};
    Point dir2 = {segment2.e.x - segment2.b.x, segment2.e.y - segment2.b.y};

    // Calculate the cross product
    float crossProduct = dir1.x * dir2.y - dir1.y * dir2.x;

    // If cross product is negative, it's a right turn
    return crossProduct < 0;
}


float angleABC(const Point &A, const Point &B, const Point &C)
{
    // Create vectors BA and BC
    Point BA = {A.x - B.x, A.y - B.y};
    Point BC = {C.x - B.x, C.y - B.y};

    // Calculate dot product and magnitudes
    float dot = dotProduct(BA, BC);
    float magBA = magnitude(BA);
    float magBC = magnitude(BC);

    // Calculate cosine of angle
    float cosTheta = dot / (magBA * magBC);

    // Return angle in radians
    return std::acos(cosTheta);
}

float clockwiseAngle(const Point& v, const Point& u) {
    float dotProduct = v.dot(u);
    float crossProduct = v.cross(u);

    // Angle in radians
    float angle = std::acos(dotProduct / (v.magnitude() * u.magnitude()));

    // Convert to degrees
    float angleInDegrees = angle * 180.0 / M_PI;

    // If cross product is negative, return the angle, else return 360 - angle
    return (crossProduct < 0) ? angleInDegrees : 360.0 - angleInDegrees;
}

sf::VertexArray calculateCircularSector(float radius, float startAngle, float arcAngle, sf::Vector2f position) {
    // Number of points on the circumference. This can be increased for smoother sectors
    const int points = 50;
    
    sf::VertexArray sector(sf::TriangleFan, points + 2);
    sector[0].position = position; // Center of the circle

    for (int i = 1; i <= points + 1; ++i) {
        // Calculate the angle for this segment of the sector
        float theta = startAngle + arcAngle * (i - 1) / points;

        // Convert polar coordinates to cartesian coordinates
        float x = position.x + radius * cos(theta);
        float y = position.y + radius * sin(theta);

        sector[i].position = sf::Vector2f(x, y);
        sector[i].color = Color::White;
    }
    
    return sector;
}

VertexArray createCircularSector(Segment segment1, Segment segment2, float local_thickness)
{
    local_thickness = thickness*5;

    Point A = segment1.b;
    Point B = segment1.e;
    Point C = segment2.e;

    float angleRad = angleABC(A, B, C);
    float angleDeg = angleRad * (180.0f / M_PI);

    Point v(1,0);
    Point u = segment2.e - segment2.b;

    cout << clockwiseAngle(v,u) << endl << endl;
    if(!isRightTurn(segment1,segment2))
        return calculateCircularSector(local_thickness, clockwiseAngle(v,u) * (3.14159265f / 180.f), (360-angleDeg) * (3.14159265f / 180.f), sf::Vector2f(B.x, N-B.y));
    return VertexArray();
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
            else
            {
                // cout << "halo" << endl;
            }
        }
          VertexArray sector = createCircularSector(polygon->segments[polygon->segments.size()-1], polygon->segments[0], thickness);
        render.sectors.push_back(sector);
        //...
    }
}


// sf::VertexArray createCircularSectorForSegments(Segment& segment1, Segment& segment2, float radius) {
//     // Ensure segments are connected
//     if (!(segment1.e == segment2.b)) {
//         throw std::runtime_error("Segments are not connected");
//     }

//     Point dir1 = (segment1.e - segment1.b).normalised();
//     Point dir2 = (segment2.b - segment2.e).normalised();  // Note the change here

//     // Calculate the starting and ending angles for our sector
//     float startAngle = std::atan2(dir1.y, dir1.x);
//     float endAngle = std::atan2(dir2.y, dir2.x);
    
//     // Adjust if startAngle is greater than endAngle
//     if (startAngle > endAngle) {
//         std::swap(startAngle, endAngle);
//     }

//     Point center = segment1.e;

//     const int points = 50;
//     sf::VertexArray sector(sf::TriangleFan, points + 2);
//     sector[0].position = sf::Vector2f(center.x, center.y);

//     for (int i = 1; i <= points + 1; ++i) {
//         float theta = startAngle + (endAngle - startAngle) * (i - 1) / points;
//         float x = center.x + radius * std::cos(theta);
//         float y = center.y + radius * std::sin(theta);
//         sector[i].position = sf::Vector2f(x, y);
//     }

//     return sector;
// }







// #pragma once
// #include <iostream>
// #include <SFML/Graphics.hpp>
// #include <cmath>
// #include "global.hpp"

// using namespace std;
// using namespace sf;

// class CircularSector
// {
// public:
//     CircularSector() {}

//     VertexArray createCircularSector(float radius, float startAngle, float arcAngle, Vector2f position)
//     {
//         // Number of points on the circumference. This can be increased for smoother sectors
//         const int points = 50;

//         sf::VertexArray sector(sf::TriangleFan, points + 2);
//         sector[0].position = position; // Center of the circle

//         for (int i = 1; i <= points + 1; ++i)
//         {
//             // Calculate the angle for this segment of the sector
//             float theta = startAngle + arcAngle * (i - 1) / points;

//             float x = position.x + radius * cos(theta);
//             float y = position.y + radius * sin(theta);

//             sector[i].position = sf::Vector2f(x, y);
//         }

//         return sector;
//     }
//     void use()
//     {
//         // Example usage: create a circular sector with 200 pixels radius, starting at 45 degrees and spanning 90 degrees
//         // sf::VertexArray sector = createCircularSector(200.f, 45.f * (3.14159265f / 180.f), 90.f * (3.14159265f / 180.f), sf::Vector2f(400, 300));
//         sf::VertexArray sector = createCircularSector(radius, 45.f * (3.14159265f / 180.f), 90.f * (3.14159265f / 180.f), sf::Vector2f(400, 300));
//         window.draw(sector);
//     }
// };