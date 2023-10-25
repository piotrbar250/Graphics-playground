#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"
#include "Point.hpp"

class WuDrawingLineAlgorithm {
public:

    static void drawLine(const Point& p1, const Point& p2)
    {
        draw(p1.x, N-p1.y, p2.x, N-p2.y, Color::Magenta);
    }

    static void draw(float x0, float y0, float x1, float y1, sf::Color color) {
        const bool steep = std::fabs(y1 - y0) > std::fabs(x1 - x0);
        if (steep) {
            std::swap(x0, y0);
            std::swap(x1, y1);
        }
        if (x0 > x1) {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }

        const float dx = x1 - x0;
        const float dy = y1 - y0;
        const float gradient = (dx == 0) ? 1 : dy / dx;

        int xpxl1 = x0;
        int xpxl2 = x1;
        float intersectY = y0;

        // Handle the first endpoint
        if (steep) {
            plot(int(y0), int(x0), rfpart(y0), color);
            plot(int(y0) + 1, int(x0), fpart(y0), color);
        } else {
            plot(int(x0), int(y0), rfpart(y0), color);
            plot(int(x0), int(y0) + 1, fpart(y0), color);
        }
        intersectY += gradient;

        // Main loop
        for (int x = xpxl1 + 1; x < xpxl2; x++) {
            if (steep) {
                plot(int(intersectY), x, rfpart(intersectY), color);
                plot(int(intersectY) + 1, x, fpart(intersectY), color);
            } else {
                plot(x, int(intersectY), rfpart(intersectY), color);
                plot(x, int(intersectY) + 1, fpart(intersectY), color);
            }
            intersectY += gradient;
        }

        // Handle the second endpoint
        if (steep) {
            plot(int(y1), int(x1), rfpart(y1), color);
            plot(int(y1) + 1, int(x1), fpart(y1), color);
        } else {
            plot(int(x1), int(y1), rfpart(y1), color);
            plot(int(x1), int(y1) + 1, fpart(y1), color);
        }
    }

private:

    // Fractional part of a number
    static float fpart(float x) {
        return x - std::floor(x);
    }

    // Remaining fractional part of a number
    static float rfpart(float x) {
        return 1 - fpart(x);
    }

    // Plot a pixel with the specified opacity (alpha)
    static void plot(int x, int y, float alpha, sf::Color color) {
        sf::RectangleShape pixel(sf::Vector2f(1, 1));
        pixel.setPosition(x, y);
        color.a = static_cast<sf::Uint8>(255 * alpha);
        pixel.setFillColor(color);
        window.draw(pixel);
    }
};