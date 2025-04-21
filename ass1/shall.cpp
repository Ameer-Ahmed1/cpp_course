#include "BoardObject.h"
#include "Tank.cpp"  // since no Tank.h
#include <iostream>  // optional for debugging

enum class Direction;  // forward declaration

class Shall : public BoardObject {
private:
    Tank& tank;         // The tank that fired the shall
    Direction dir;      // Direction of movement

public:
    Shall(Point p, Tank& t, Direction d)
        : BoardObject(p), tank(t), dir(d) {}

    void somePureVirtualFunction() override {
        // Nothing for now
    }

    int moveShall() {
        // TODO: implement movement logic
        return 0;
    }
};
