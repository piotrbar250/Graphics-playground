#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"
#include "Point.hpp"

using namespace std;
using namespace sf;

class NaiveDrawingLineAlgorithm
{
public:
    static void putPixel(int x, int y)
    {
        Vertex vertex[1];
        vertex[0] = Vector2f(x, N - y);
        vertex[0].color = Color::Magenta;
        window.draw(vertex, 1, Points);
    }

    static void drawLine(const Point &a, const Point b)
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
            float b = float(y1) - m * x1;
            if (m >= -1.0 and m <= 1)
            {
                if (x1 > x2)
                    swap(x1, x2);

                for (int x = x1; x <= x2; x++)
                    putPixel(x, round(m * x + b));
            }
            else if (m >= 1.0 or m <= -1.0)
            {
                if (y1 > y2)
                    swap(y1, y2);

                for (int y = y1; y <= y2; y++)
                    putPixel(round(float((y - b)) / m), y);
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