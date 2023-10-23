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

    // void createButton()
    // {
    //     Button button(200, 100, 300, 500, relationsButtonOFF);
    //     Button button2(200, 100, 0, 30, relationsButtonOFF);

    //     render.buttons.push_back(button);
    //     render.buttons.push_back(button2);
    // }

    void mouseClickHandler(const Point &cursorPoint)
    {
        for(Polygon*& polygon: render.polygons)
        {
            for(Segment& segment: polygon->segments)
            {
                if(segment.button1->isMouseOver(cursorPoint))
                {
                    segment.relation1 = !segment.relation1;
                }
                if(segment.button2->isMouseOver(cursorPoint))
                {
                    segment.relation2 = !segment.relation2;
                }
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
                Point pos = segment.middle() + l.verticalVector * 80;
                Point pos2 = {pos.x, pos.y - 25};
                Point pos3 = {pos.x, pos.y - 50};

                Button* button = new Button(20, 20, pos.x, pos.y, relationsButtonOFF);
                Button* button2 = new Button(20, 20, pos2.x, pos2.y, relationsButtonOFF);
                Button* button3 = new Button(20, 20, pos3.x, pos3.y, relationsButtonOFF);

                if(segment.relation1)
                    button->btn.setFillColor(relationsButtonON);
                
                if(segment.relation2)
                    button2->btn.setFillColor(relationsButtonON);

                if(segment.relation3)
                    button3->btn.setFillColor(relationsButtonON);

                // DELETE
                if(segment.button1)
                {
                    delete segment.button1;
                    segment.button1 = nullptr;
                }
                if(segment.button2)
                {
                    delete segment.button2;
                    segment.button2 = nullptr;
                }
                if(segment.button3)
                {
                    delete segment.button3;
                    segment.button2 = nullptr;
                }

                segment.button1 = button;
                segment.button2 = button2;
                segment.button3 = button3;


                buttons.push_back(*button);
                buttons.push_back(*button2);
                buttons.push_back(*button3);

                // render.tm.push_back(segment.middle() + l.verticalVector * 40);
            }
        }

        render.buttons = buttons;
    }
};