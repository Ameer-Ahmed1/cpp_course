#include "BoardObject.h"
#include <iostream>

class Wall : public BoardObject {
public:
    Wall(Point p) : BoardObject(p) {}

    void somePureVirtualFunction() override {
        // May be empty or contain shared wall logic
    }

    virtual std::string getWallType() const = 0;  // force derived classes to define their type
};
