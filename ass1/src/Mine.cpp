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
    int onCollideWithShell() override {
        return -1;
    }
};
