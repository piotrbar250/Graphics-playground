#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"
#include "Point.hpp"

using namespace std;
using namespace sf;

class BresenhamDrawingLineAlgorithm
{
public:
    static void putPixel(int x, int y)
    {
        Vertex vertex[1];
        vertex[0] = Vector2f(x, N - y);
        vertex[0].color = Color::Red;
        window.draw(vertex, 1, Points);
    }

    static void drawLine(const Point &a, const Point &b, int thickness)
    {
        int x1 = a.x;
        int y1 = a.y;

        int x2 = b.x;
        int y2 = b.y;

        int rise = y2 - y1;
        int run = x2 - x1;

        float length = sqrt(run * run + rise * rise);
        int dx = -rise * thickness / length;
        int dy = run * thickness / length;

        for (int i = -thickness / 2; i <= thickness / 2; i++)
        {
            int offset_x = i * dx / thickness;
            int offset_y = i * dy / thickness;
            drawSingleLine(Point(x1 + offset_x, y1 + offset_y), Point(x2 + offset_x, y2 + offset_y));
        }
    }

    static void drawSingleLine(const Point &a, const Point b)
    {
        int x1 = a.x;
        int y1 = a.y;

        int x2 = b.x;
        int y2 = b.y;

        int rise = y2 - y1;
        int run = x2 - x1;

        if (run != 0)
        {
            float m = float(rise) / run;
            int adjust = m >= 0 ? 1 : -1;
            int offset = 0;

            if (m >= -1.0 and m <= 1)
            {
                int delta = fabs(rise) * 2;
                int treshold = fabs(run);
                int tresholdInc = fabs(run) * 2;
                int y = y1;

                if (x1 > x2)
                {
                    swap(x1, x2);
                    y = y2;
                }

                for (int x = x1; x <= x2; x++)
                {
                    putPixel(x, y);
                    offset += delta;
                    if (offset >= treshold)
                    {
                        y += adjust;
                        treshold += tresholdInc;
                    }
                }
            }
            else if (m >= 1.0 or m <= -1.0)
            {
                int delta = fabs(run) * 2;
                int treshold = fabs(rise);
                int tresholdInc = fabs(rise) * 2;
                int x = x1;

                if (y1 > y2)
                {
                    swap(y1, y2);
                    x = x2;
                }

                for (int y = y1; y <= y2; y++)
                {
                    putPixel(x, y);
                    offset += delta;
                    if (offset >= treshold)
                    {
                        x += adjust;
                        treshold += tresholdInc;
                    }
                }
            }
        }
        else
        {
            if (y1 > y2)
                swap(y1, y2);

            for (int y = y1; y <= y2; y++)
                putPixel(x1, y);
        }
    }
};