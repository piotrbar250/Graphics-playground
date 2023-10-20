#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace std;
using namespace sf;

enum Mode {
    DRAWING,
    EDITING
};


// extern int M = 1152, N = 720; // const ?? 
const int M = 1152, N = 720;
const float radius = 10;
extern RenderWindow window;
extern Mode currentMode; 


// add singleton
/*


std::vector<std::shared_ptr<Polygon>> vec;
auto polPtr = std::make_shared<Polygon>();
vec.push_back(polPtr);


Using pointers or smart pointers means you're storing a reference to the original object, and not a copy. But remember, if you're using raw pointers, you need to ensure the lifetime of the object being pointed to outlives the pointer. With smart pointers, the memory management is handled for you, but you still need to be aware of ownership and the object's lifetime.
*/

/*
Example of two classes comunicating with each other
also in c# !!
*/

/*
Does copying class object calls constructor of it
*/