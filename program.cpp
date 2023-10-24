#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "global.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Polygon.hpp"
#include "Render.hpp"
#include "PolygonDrawer.hpp"
#include "PolygonEditor.hpp"
#include "PolygonVertexRemovingEditor.hpp"
#include "PolygonVertexInsertingEditor.hpp"
#include "PolygonMovingEditor.hpp"
#include "ButtonDrawer.hpp"
#include "VerticalRelationEditor.hpp"
#include "HorizontalRelationEditor.hpp"
#include "AdjacentEdgesRelationEditor.hpp"
#include "NaiveDrawingLineAlgorithm.hpp"
#include "BresenhamDrawingLineAlgorithm.hpp"
#include "CircularSector.hpp"
using namespace std;
using namespace sf;

RenderWindow window;
Mode currentMode;
Algorithm currentAlgorithm;

// float magnitude(const Point &v)
// {
//     return std::sqrt(v.x * v.x + v.y * v.y);
// }

// float dotProduct(const Point &a, const Point &b)
// {
//     return a.x * b.x + a.y * b.y;
// }

// float angleBetweenSegments(const Segment &s1, const Segment &s2)
// {
//     // Find the directional vectors
//     Point v1 = {s1.e.x - s1.b.x, s1.e.y - s1.b.y};
//     Point v2 = {s2.e.x - s2.b.x, s2.e.y - s2.b.y};

//     // Calculate the dot product and magnitudes
//     float dot = dotProduct(v1, v2);
//     float mag1 = magnitude(v1);
//     float mag2 = magnitude(v2);

//     // Calculate the cosine of the angle
//     float cosTheta = dot / (mag1 * mag2);

//     // Return the angle in radians
//     return std::acos(cosTheta);
// }

// float signedAngleBetweenSegments(const Segment &s1, const Segment &s2)
// {
//     Point v1 = {s1.e.x - s1.b.x, s1.e.y - s1.b.y};
//     Point v2 = {s2.e.x - s2.b.x, s2.e.y - s2.b.y};

//     // Calculate the determinant
//     float determinant = v1.x * v2.y - v1.y * v2.x;
//     float dot = dotProduct(v1, v2);
//     float angleRad = std::atan2(determinant, dot);

//     // Make sure the angle is positive
//     if (angleRad < 0)
//     {
//         angleRad += 2 * M_PI;
//     }

//     return angleRad;
// }

// float angleABC(const Point &A, const Point &B, const Point &C)
// {
//     // Create vectors BA and BC
//     Point BA = {A.x - B.x, A.y - B.y};
//     Point BC = {C.x - B.x, C.y - B.y};

//     // Calculate dot product and magnitudes
//     float dot = dotProduct(BA, BC);
//     float magBA = magnitude(BA);
//     float magBC = magnitude(BC);

//     // Calculate cosine of angle
//     float cosTheta = dot / (magBA * magBC);

//     // Return angle in radians
//     return std::acos(cosTheta);
// }

// float angleWithHorizontal(const Point& A, const Point& B) {
//     // Check for vertical line
//     if (A.x == B.x) {
//         return M_PI / 2; // 90 degrees in radians
//     }

//     // Calculate slope
//     float m = (B.y - A.y) / (B.x - A.x);

//     // Return angle in radians
//     return std::atan(m);
// }


// //------
// float clockwiseAngle(const Point& v, const Point& u) {
//     float dotProduct = v.dot(u);
//     float crossProduct = v.cross(u);

//     // Angle in radians
//     float angle = std::acos(dotProduct / (v.magnitude() * u.magnitude()));

//     // Convert to degrees
//     float angleInDegrees = angle * 180.0 / M_PI;

//     // If cross product is negative, return the angle, else return 360 - angle
//     return (crossProduct < 0) ? angleInDegrees : 360.0 - angleInDegrees;
// }

int main()
{
    window.create(sf::VideoMode(1152, 720), "Polygon editor");
    window.display();

    currentMode = DRAWING;
    currentAlgorithm = LIBRARY;
    Render render;

    PolygonDrawer polygonDrawer(render);
    PolygonEditor *polygonEditor = new PolygonEditor(render);
    PolygonVertexRemovingEditor *polygonVertexRemovingEditor;
    PolygonVertexInsertingEditor *polygonVertexInsertingEditor;
    PolygonMovingEditor *polygonMovingEditor;

    ButtonDrawer buttonDrawer(render);

    VerticalRelationEditor verticalRelationEditor(render);
    HorizontalRelationEditor horizontalRelationEditor(render);
    AdjacentEdgesRelationEditor adjacentEdgesRelationEditor(render);
    // buttonDrawer.createButton();

    bool displayRelationMenu = false;

    bool polygonStarted = false;

    int i = 0;
    while (window.isOpen())
    {

        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed and event.key.code == Keyboard::E)
            {
                polygonEditor = new PolygonEditor(render);
                currentMode = EDITING;
            }
            if (event.type == Event::KeyPressed and event.key.code == Keyboard::R)
            {
                polygonVertexRemovingEditor = new PolygonVertexRemovingEditor(render);
                currentMode = VERTEX_REMOVING;
            }
            if (event.type == Event::KeyPressed and event.key.code == Keyboard::I)
            {
                polygonVertexInsertingEditor = new PolygonVertexInsertingEditor(render);
                currentMode = VERTEX_INSERTING;
            }
            if (event.type == Event::KeyPressed and event.key.code == Keyboard::M)
            {
                polygonMovingEditor = new PolygonMovingEditor(render);
                currentMode = POLYGON_MOVING;
            }
            if (event.type == Event::KeyPressed and event.key.code == Keyboard::D)
            {
                displayRelationMenu = !displayRelationMenu;
            }
            if (event.type == Event::KeyPressed and event.key.code == Keyboard::X)
            {
                // polygonMovingEditor = new PolygonMovingEditor(render);
                if (currentMode == DRAWING)
                    currentMode = TESTING;
                else if (currentMode == TESTING)
                    currentMode = DRAWING;
                else
                {
                    cout << "UNDEFINED BEHAVIOUR" << endl;
                    return 0;
                }
            }
            if (event.type == Event::KeyPressed and event.key.code == Keyboard::A)
            {
                // polygonMovingEditor = new PolygonMovingEditor(render);
                if (currentAlgorithm == LIBRARY)
                    currentAlgorithm = BRESENHAM;
                else if (currentAlgorithm == BRESENHAM)
                    currentAlgorithm = LIBRARY;
                else
                {
                    cout << "UNDEFINED BEHAVIOUR" << endl;
                    return 0;
                }
            }

            if (event.type == Event::MouseButtonPressed)
            {
                Point cursorPoint(Point::ctd(Point(event.mouseButton.x, event.mouseButton.y)));

                if (currentMode == DRAWING)
                {
                    polygonDrawer.mouseClickHandler(cursorPoint);
                }
                else if (currentMode == EDITING)
                {
                    polygonEditor->mouseClickHandler(cursorPoint);
                }
                else if (currentMode == VERTEX_REMOVING)
                {
                    polygonVertexRemovingEditor->mouseClickHandler(cursorPoint);
                }
                else if (currentMode == VERTEX_INSERTING)
                {
                    polygonVertexInsertingEditor->mouseClickHandler(cursorPoint);
                    // delete polygonVertexInsertingEditor;
                }
                else if (currentMode == POLYGON_MOVING)
                {
                    polygonMovingEditor->mouseClickHandler(cursorPoint);
                    // delete polygonVertexInsertingEditor;
                }
                else if (currentMode == TESTING)
                {
                    buttonDrawer.mouseClickHandler(cursorPoint);
                    // delete polygonVertexInsertingEditor;
                }
            }
        }

        if (currentMode == DRAWING)
        {
            polygonDrawer.temporarySegmentHanlder();
        }
        else if (currentMode == EDITING)
        {
            polygonEditor->temporarySegmentHanlder();
        }
        else if (currentMode == POLYGON_MOVING)
        {
            polygonMovingEditor->temporaryPolygonHandler();
        }

        if (displayRelationMenu)
        {
            cout << "weszlem " << i++ << endl;
            buttonDrawer.displayRelationMenu();
        }

        // adjacentEdgesRelationEditor.adjustRelations(polygonDrawer);
        verticalRelationEditor.adjustPlain(polygonDrawer);
        horizontalRelationEditor.adjustPlain(polygonDrawer);
        adjacentEdgesRelationEditor.adjustPlain(polygonDrawer);
        createCircularSectors(render);
        window.clear();

        render.draw();


        // // Point p4 = {100, 100};
        // // Point p3 = {200, 650};
        // // Point p2 = {200, 650};
        // // Point p1 = {500, 100};

        // Point p1 = {100, 100};
        // Point p2 = {500, 100};
        // Point p3 = {500, 100};
        // Point p4 = {700, 400};
        // Segment segment1(p1, p2);
        // Segment segment2(p3, p4);

        // BresenhamDrawingLineAlgorithm::drawLine(p1, p2, thickness);
        // BresenhamDrawingLineAlgorithm::drawLine(p3, p4, thickness);


        // Point A = p1;
        // Point B = p2; // Also p3
        // Point C = p4;

        // float angleRad = angleABC(A, B, C);

        // // Convert angle from radians to degrees if needed
        // float angleDeg = angleRad * (180.0f / M_PI);

        // // Print the angle in degrees
        // std::cout << "Angle ABC in degrees: " << 360 - angleDeg << std::endl;

        // Point ab = p4 - p3;
        // Point u = p4 - p3;
        // Point v(1,0);


        // cout << "v: " << v << endl; 
        // std::cout << "Clockwise angle between vectors: " << clockwiseAngle(v, u) << " degrees" << std::endl;

        // // VertexArray sector = createCircularSector(30, clockwiseAngle(v, u), 360-angleDeg, Vector2f(B.x, N-B.y));
        // // VertexArray sector = createCircularSector(10.f, clockwiseAngle(v, u) * (3.14159265f / 180.f), (360-angleDeg) * (3.14159265f / 180.f), sf::Vector2f(B.x, N-B.y));
        // VertexArray sector = calculateCircularSector(10.f, clockwiseAngle(v,u) * (3.14159265f / 180.f), (360-angleDeg) * (3.14159265f / 180.f), sf::Vector2f(B.x, N-B.y));

        // window.draw(sector);
 
        // // float angleRad = signedAngleBetweenSegments(segment1, segment2);

        // // Convert angle from radians to degrees if needed
        // // float angleDeg = angleRad * (180.0f / M_PI);

        // // Print the angle in degrees
        // // std::cout << "Angle in degrees: " << angleDeg << " " << 360 - angleDeg << std::endl;
        // // returns Angle in degrees: 108.435 251.565 which is clearly wrong - one degree is below 90



        window.display();
    }
}