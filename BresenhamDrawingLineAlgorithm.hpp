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

    // static void drawLine(const Point &a, const Point &b, int thickness=5)
    // {
    //     int x1 = a.x;
    //     int y1 = a.y;

    //     int x2 = b.x;
    //     int y2 = b.y;

    //     int rise = y2 - y1;
    //     int run = x2 - x1;

    //     float length = sqrt(run * run + rise * rise);
    //     int dx = -rise * thickness / length;
    //     int dy = run * thickness / length;

    //     for (int i = -thickness / 2; i < thickness / 2; i++)
    //     {
    //         drawSingleLine(Point(x1 + i * dx / thickness, y1 + i * dy / thickness), Point(x2 + i * dx / thickness, y2 + i * dy / thickness));
    //     }
    // }

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

    static void drawLine3(const Point &a, const Point &b)
    {
        int x1 = a.x;
        int y1 = a.y;

        int x2 = b.x;
        int y2 = b.y;

        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);

        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;

        // Handling special cases where run is 0
        if (dx == 0)
        {
            for (int y = y1; y != y2 + sy; y += sy)
            {
                putPixel(x1, y);
            }
            return;
        }

        // Handling cases based on the slope of the line
        if (dy <= dx)
        {
            int p = 2 * dy - dx;
            int y = y1;
            for (int x = x1; x != x2 + sx; x += sx)
            {
                putPixel(x, y);
                if (p >= 0)
                {
                    y += sy;
                    p -= 2 * dx;
                }
                p += 2 * dy;
            }
        }
        else
        {
            int p = 2 * dx - dy;
            int x = x1;
            for (int y = y1; y != y2 + sy; y += sy)
            {
                putPixel(x, y);
                if (p >= 0)
                {
                    x += sx;
                    p -= 2 * dy;
                }
                p += 2 * dx;
            }
        }
    }

    static void drawLine5(const Point &a, const Point &b)
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
            int delta, threshold, thresholdInc;
            float offset = 0.0f;

            if (m >= -1.0 and m <= 1.0)
            {
                delta = 2 * abs(rise);
                threshold = abs(run);
                thresholdInc = 2 * abs(run);
                int y = y1;

                if (x1 > x2)
                {
                    swap(x1, x2);
                    y = y2;
                    rise = -rise;
                }

                for (int x = x1; x <= x2; x++)
                {
                    putPixel(x, y);
                    offset += delta;
                    if (offset >= threshold)
                    {
                        y += (rise > 0 ? 1 : -1);
                        threshold += thresholdInc;
                    }
                }
            }
            else
            {
                delta = 2 * abs(run);
                threshold = abs(rise);
                thresholdInc = 2 * abs(rise);
                int x = x1;

                if (y1 > y2)
                {
                    swap(y1, y2);
                    x = x2;
                    run = -run;
                }

                for (int y = y1; y <= y2; y++)
                {
                    putPixel(x, y);
                    offset += delta;
                    if (offset >= threshold)
                    {
                        x += (run > 0 ? 1 : -1);
                        threshold += thresholdInc;
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