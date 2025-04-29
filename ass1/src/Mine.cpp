#include "BoardObject.h"
#include <iostream>

class Mine : public BoardObject {
private:
    bool active;  // Determines if the mine is active or not

public:
    Mine(Point p, bool isActive)
        : BoardObject(p), active(isActive) {}

    bool isActive() const {
        return active;
    }

    void deactivate() {
        active = false;  // Deactivates the mine
    }

    void activate() {
        active = true;   // Activates the mine
    }
    
    BoardObjectType getObjectType() const override {
        return BoardObjectType::Mine;
    }



    /*int collidedWithObject(BoardObject& object) override {// Return value: winner's ID (1 or 2), 0 for invalid move, or -1 if nothing happens.
        BoardObjectType type = object.getObjectType();
        switch (type) {
            case BoardObjectType::Tank: {return (object.id == 1) ? 2 : 1;}
            default: {return -1;}
        }
    }*/
};
