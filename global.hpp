#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace std;
using namespace sf;

enum Mode {
    DRAWING,
    EDITING,
    VERTEX_REMOVING
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