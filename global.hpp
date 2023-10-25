#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace std;
using namespace sf;

enum Mode {
    DRAWING,
    EDITING,
    VERTEX_REMOVING,
    VERTEX_INSERTING,
    POLYGON_MOVING,
    TESTING,
    SLIDER
};

enum Algorithm{
    LIBRARY,
    NAIVE,
    BRESENHAM,
    WU
};


const int M = 1152, N = 720;
const float radius = 10;
const float thickness = 6;
extern float offsetThickness; // 6;
const float eps = thickness/2.0f;
const bool displayDefault = true; 

const Color relationsButtonON = Color::Cyan;
const Color relationsButtonOFF = Color::Red;

extern RenderWindow window;
extern Mode currentMode; 
extern Algorithm currentAlgorithm;