#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Point.hpp"
#include "Polygon.hpp"
#include "global.hpp"
#include "Line.hpp"
#include "Button.hpp"
#include "BresenhamDrawingLineAlgorithm.hpp"
#include "NaiveDrawingLineAlgorithm.hpp"
#include "WuDrawingLineAlgorithm.hpp"
#include "Slider.hpp"

// #include "CircularSector.hpp"
using namespace std;
using namespace sf;

class Render
{
public:
    vector<Polygon *> polygons;
    vector<Line> lines;
    vector<Button> buttons;

    vector<Point> tmpVertexes;
    vector<Segment> tmpSegments;

    vector<VertexArray> sectors;

    vector<RectangleShape> offsetRecatngles;
    vector<RectangleShape> segmentRectangles;

    Render() : polygons(vector<Polygon *>()) {}

    void drawPoint(const Point &p)
    {
        Vertex v(Vector2f(dtc(p).x, dtc(p).y));
        Vertex vA[] = {v};
        window.draw(vA, 1, Points);
    }

    float magnitude(const Point &v)
    {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    float dotProduct(const Point &a, const Point &b)
    {
        return a.x * b.x + a.y * b.y;
    }

    bool isRightTurn(const Segment &segment1, const Segment &segment2)
    {
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

    void prepareSegments(const Segment &seg)
    {
        if (currentAlgorithm == BRESENHAM)
        {
            BresenhamDrawingLineAlgorithm::drawLine(seg.b, seg.e, thickness);
            return;
        }
        if (currentAlgorithm == WU)
        {
            offsetThickness = 0;
            WuDrawingLineAlgorithm::drawLine(seg.b, seg.e);
            return;
        }

        float x1 = seg.b.x;
        float y1 = seg.b.y;

        float x2 = seg.e.x;
        float y2 = seg.e.y;

        float len = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
        float angle_rad = atan2(y1 - y2, x2 - x1);
        float angle_deg = angle_rad * 180 / M_PI;

        RectangleShape rect(Vector2f(len, thickness));
        rect.setPosition(Vector2f(dtc(seg.b).x, dtc(seg.b).y));
        rect.rotate(angle_deg);

        rect.setFillColor(Color::Green);
        segmentRectangles.push_back(rect);

    }

    bool determineDirection(Polygon *polygon)
    {
        int sum = 0;
        for (int i = 1; i < polygon->vertexes.size(); i++)
        {
            sum += (polygon->vertexes[i].x - polygon->vertexes[i - 1].x) * (polygon->vertexes[i].y + polygon->vertexes[i - 1].y);
        }
        if (sum < 0)
            return true;
        return false;
    }

    Point findIntersection(const Line &line1, const Line &line2)
    {
        float determinant = line1.A * line2.B - line2.A * line1.B;

        float x = (line1.B * line2.C - line2.B * line1.C) / determinant;
        float y = (line2.A * line1.C - line1.A * line2.C) / determinant;

        return {x, y};
    }

    void createOffset(Polygon *polygon)
    {
        for (int i = 0; i < polygon->segments.size(); i++)
        {
            Segment &segment = polygon->segments[i];
            Line l(segment.b, segment.e);

            segment.bShifted = segment.b + l.verticalVector.normalised() * (offsetThickness);
            segment.eShifted = segment.e + l.verticalVector.normalised() * (offsetThickness);

            if (!determineDirection(polygon))
            {
                segment.bShifted = segment.b - l.verticalVector.normalised() * (offsetThickness);
                segment.eShifted = segment.e - l.verticalVector.normalised() * (offsetThickness);
            }
            polygon->segments[i].bShifted = segment.bShifted;
            polygon->segments[i].eShifted = segment.eShifted;
        }



        for (int i = 0; i < polygon->segments.size() - 1; i++)
        {
            Point A = polygon->segments[i].b;
            Point B = polygon->segments[i].e;
            Point C = polygon->segments[i + 1].e;

            float angleRad = angleABC(A, B, C);
            float angleDeg = angleRad * (180.0f / M_PI);

            if (((!isRightTurn(polygon->segments[i], polygon->segments[i + 1])) && determineDirection(polygon)) or (isRightTurn(polygon->segments[i], polygon->segments[i + 1]) && !determineDirection(polygon)))
                angleDeg = 360 - angleDeg;
            // cout << angleDeg << endl;

            if (angleDeg < 180)
            {
                Segment s1 = polygon->segments[i];
                Segment s2 = polygon->segments[i + 1];

                Line para(s1.bShifted, s1.eShifted);
                Line nextLine(s2.b, s2.e);

                // cout << "stary " << polygon->segments[i].bShifted << endl;
                polygon->segments[i].eShifted = findIntersection(para, nextLine);
                // cout << "nowy " << polygon->segments[i].bShifted << endl;

                para = Line(s2.bShifted, s2.eShifted);
                Line prevLine(s1.b, s1.e);
                polygon->segments[i + 1].bShifted = findIntersection(para, prevLine);
            }

            tmpVertexes.push_back(polygon->segments[i].bShifted);
            tmpVertexes.push_back(polygon->segments[i].eShifted);

        }

        int i = polygon->segments.size() - 1;
        Point A = polygon->segments[i].b;
        Point B = polygon->segments[i].e;
        Point C = polygon->segments[0].e;

        float angleRad = angleABC(A, B, C);
        float angleDeg = angleRad * (180.0f / M_PI);

        if (((!isRightTurn(polygon->segments[i], polygon->segments[0])) && determineDirection(polygon)) or (isRightTurn(polygon->segments[i], polygon->segments[0]) && !determineDirection(polygon)))
            angleDeg = 360 - angleDeg;
        // cout << angleDeg << endl;

        if (angleDeg < 180)
        {
            Segment s1 = polygon->segments[i];
            Segment s2 = polygon->segments[0];

            Line para(s1.bShifted, s1.eShifted);
            Line nextLine(s2.b, s2.e);

            // cout << "stary " << polygon->segments[i].bShifted << endl;
            polygon->segments[i].eShifted = findIntersection(para, nextLine);
            // cout << "nowy " << polygon->segments[i].bShifted << endl;

            para = Line(s2.bShifted, s2.eShifted);
            Line prevLine(s1.b, s1.e);
            polygon->segments[0].bShifted = findIntersection(para, prevLine);
        }

        tmpVertexes.push_back(polygon->segments[i].bShifted);
        tmpVertexes.push_back(polygon->segments[i].eShifted);



        for (int i = 0; i < polygon->segments.size() - 1; i++)
        {
            Point A = polygon->segments[i].b;
            Point B = polygon->segments[i].e;
            Point C = polygon->segments[i + 1].e;

            float angleRad = angleABC(A, B, C);
            float angleDeg = angleRad * (180.0f / M_PI);

            if (!isRightTurn(polygon->segments[i], polygon->segments[i + 1]))
                angleDeg = 360 - angleDeg;
            // cout << angleDeg << endl;
        }

        for (int i = 0; i < polygon->segments.size(); i++)
        {
            Segment segment = polygon->segments[i];

            Segment pom(segment.bShifted, segment.eShifted);
      

            float x1 = pom.b.x;
            float y1 = pom.b.y;

            float x2 = pom.e.x;
            float y2 = pom.e.y;

            float len = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
            float angle_rad = atan2(y1 - y2, x2 - x1);
            float angle_deg = angle_rad * 180 / M_PI;

            Line l(segment.b, segment.e);
            

            Point przesuniecie = segment.b - segment.bShifted;
            przesuniecie = segment.bShifted - pom.b;
            przesuniecie = l.verticalVector.normalised()*offsetThickness;
            if(!determineDirection(polygon))
                przesuniecie = przesuniecie * 0;
            RectangleShape rect2(Vector2f(len, offsetThickness));
            rect2.setPosition(Vector2f(dtc(pom.b - przesuniecie).x, dtc(pom.b-przesuniecie).y));
            rect2.rotate(angle_deg);

            rect2.setFillColor(Color::White);

            offsetRecatngles.push_back(rect2);
        }
    }

    void drawCircle(const Point &p, Color color = Color::Blue)
    {
        CircleShape circle(radius);
        circle.setFillColor(color);
        circle.setPosition(Vector2f(dtc(p).x - radius, dtc(p).y - radius));
        window.draw(circle);
    }

    void drawButton(const Button &button)
    {
        button.draw();
    }

    void drawLine(const Line &line)
    {
        line.draw();
    }

    void draw()
    {
        for (auto &sector : sectors)
            window.draw(sector);

        int i = 0;
        for (auto &polygon : polygons)
        {
            for (auto &seg : polygon->segments)
                prepareSegments(seg);
        }

        for (RectangleShape &rect : offsetRecatngles)
            window.draw(rect);
        offsetRecatngles.clear();

        for (RectangleShape &rect : segmentRectangles)
            window.draw(rect);
        segmentRectangles.clear();

        for (auto &polygon : polygons)
        {
            for (auto &p : polygon->vertexes)
                drawCircle(p);
        }

        for (Button &button : buttons)
        {
            button.draw();
        }
        buttons.clear();

        tmpVertexes.clear();
        for (auto &polygon : polygons)
        {
            createOffset(polygon);
        }

        // for (auto &v : tmpVertexes)
        //     drawCircle(v, Color::Yellow);
    }

    void addPolygon(Polygon *polygon)
    {
        polygons.push_back(polygon);
    }
};