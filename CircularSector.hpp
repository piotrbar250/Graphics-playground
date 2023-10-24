#pragma once
#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include "global.hpp"
#include <cmath>


sf::VertexArray createCircularSector(float radius, float startAngle, float arcAngle, sf::Vector2f position) {
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
    }
    
    return sector;
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