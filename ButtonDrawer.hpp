#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "global.hpp"
#include "Button.hpp"
#include "Render.hpp"

class ButtonDrawer
{
public:
    Render& render;
    ButtonDrawer(Render& render) : render(render) {}

    void createButton()
    {
        Button button(200, 100, 300, 500, relationsButtonOFF);
        Button button2(200, 100, 0, 30, relationsButtonOFF);

        render.buttons.push_back(button);
        render.buttons.push_back(button2);
    }

    void mouseClickHandler(const Point &cursorPoint)
    {
        for(Button& button: render.buttons)
        {
            if(button.isMouseOver(cursorPoint))
                button.swapColor();
        }

        for(Polygon*& polygon: render.polygons)
        {
            for(Segment& segment: polygon->segments)
            {
                if(segment.button1->isMouseOver(cursorPoint))
                {
                    segment.relation1 = !segment.relation1;
                }
                // if(button.isMouseOver(cursorPoint))
                // {

                // }
            }
        }
    }

    void displayRelationMenu()
    {
        vector<Button> buttons;

        for(Polygon*& polygon: render.polygons)
        {
            for(Segment& segment: polygon->segments)
            {
                Line l(segment.b, segment.e);

                // render.tmpVertexes.push_back(segment.middle() + l.verticalVector * 40);
                Point pos = segment.middle() + l.verticalVector * 40;
                
                Button* button = new Button(20, 20, pos.x, pos.y, relationsButtonOFF);

                if(segment.relation1)
                    button->btn.setFillColor(relationsButtonON);

                // DELETE
                if(segment.button1)
                {
                    delete segment.button1;
                    segment.button1 = nullptr;
                }
                
                segment.button1 = button;
                buttons.push_back(*button);

                // render.tm.push_back(segment.middle() + l.verticalVector * 40);
            }
        }

        render.buttons = buttons;
    }
};