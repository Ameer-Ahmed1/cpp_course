#pragma once
#include "Point.h"
#include "Enums.h"
class BoardObject {
protected:
    static int h;  // board height
    static int w;  // board width
    Point pos;  // Position of the object
    // Constructor: Prevents direct instantiation of BoardObject
    BoardObject(Point p) : pos(p) {}

public:
    virtual ~BoardObject() = default;  // Virtual destructor

    // Pure virtual function makes BoardObject an abstract class
    virtual void somePureVirtualFunction() = 0;

    // Static function for collision check, now returning true/false
    static bool checkColl(const BoardObject& a, const BoardObject& b) {
        return (a.pos.x == b.pos.x && a.pos.y == b.pos.y);  // Returns true or false
    }
    static void setBoardSize(int height, int width) {
        h = height;
        w = width;
    }
    
};
