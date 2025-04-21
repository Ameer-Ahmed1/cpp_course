#pragma once
#include "Point.h"
#include "Enums.h"
class BoardObject {
protected:
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
};
