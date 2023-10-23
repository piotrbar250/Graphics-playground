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
    TESTING
};


// extern int M = 1152, N = 720; // const ?? 
const int M = 1152, N = 720;
const float radius = 10;
const float thickness = 6;
const float eps = thickness/2;

const Color relationsButtonON = Color::Cyan;
const Color relationsButtonOFF = Color::Red;

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

/*
comparing two variables based on the memory, pointer
*/

/*
what was deep copying and do vectors perform deep copying
if i have a vector<segment> vec and also vector<segment> tmp and I do vec = tmp does it copy or reference
ChatGPT
When you do vec = tmp with std::vector<Segment> vec and std::vector<Segment> tmp, it performs a copy assignment. This means:

The elements in vec are replaced by a copy of the elements in tmp.
The size of vec becomes the same as tmp.
After the assignment, vec and tmp are two separate vectors with their own copies of the data. Modifying an element in one vector won't affect the other vector.
It's not a reference assignment; the two vectors don't share the same underlying data after the assignment. The assignment operator for std::vector creates a deep copy of the elements from the source vector (tmp) to the destination vector (vec).
*/

/*
returning reference to the local variable
*/

/*

Yes, you can avoid creating Point.cpp by restructuring your code to prevent calling methods of the Line class directly in the Point class header.

One way to achieve this is by using a function pointer or a lambda function. Here's an approach using a lambda function:

Modify the pointOnLine method to accept a lambda function.
The caller will pass the lambda which calls the method of the Line class.
Here's how you can implement it:

Point.hpp:

cpp
Copy code
#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <functional>

class Point
{
public:
    float x, y;
    Point(float x, float y) : x(x), y(y) {}

    void print()
    {
        std::cout << x << " " << y;
    }

    void pointOnLine(const std::function<void()>& fun)
    {
        fun();
    }
};

#endif
main.cpp:

cpp
Copy code
#include <iostream>
#include "Point.hpp"
#include "Line.hpp"
using namespace std;

int main()
{
    // Example to call the pointOnLine with a lambda
    Point p(5, 3);
    Line l;

    p.pointOnLine([&]() {
        l.someFun();
    });

    l.print();

    cout << endl;
}
In this approach:

The pointOnLine method of the Point class accepts a lambda function (or any callable).
When you want a Point to invoke a method on a Line, you pass the method wrapped inside a lambda to pointOnLine.
With this setup, there's no need for Point to know about Line methods directly, thus eliminating the cyclic dependency without adding a Point.cpp.

*/