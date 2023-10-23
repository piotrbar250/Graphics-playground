#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"
#include "Point.hpp"

class Button
{
public:
    RectangleShape btn;
    Point leftTop, rightBottom;

    Button(float width, float height, float posX, float posY, Color color)
    {   
        leftTop = {posX, posY};
        rightBottom = {posX + width, posY - height};

        btn.setSize(Vector2f(width, height));
        btn.setPosition(Vector2f(posX, N-posY));
        btn.setFillColor(color);
    }

    void draw() const
    {
        window.draw(btn);
    }

    void swapColor()
    {
        if(btn.getFillColor() == relationsButtonOFF)
            btn.setFillColor(relationsButtonON);
        else
            btn.setFillColor(relationsButtonOFF);
    }

    bool isMouseOver(const Point &cursorPoint)
    {
        if(leftTop.x <= cursorPoint.x and cursorPoint.x <= rightBottom.x and
            rightBottom.y <= cursorPoint.y and cursorPoint.y <= leftTop.y)
            return true;
        return false;
    }
};