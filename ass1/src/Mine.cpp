#include "BoardObject.h"
#include <iostream>

class Mine : public BoardObject {
private:
    bool active;  // Determines if the mine is active or not

public:
    Mine(Point p, bool isActive)
        : BoardObject(p), active(isActive) {}

    void somePureVirtualFunction() override {
        // Optional: Implement behavior for this specific Mine type
    }

    bool isActive() const {
        return active;
    }

    void deactivate() {
        active = false;  // Deactivates the mine
    }

    void activate() {
        active = true;   // Activates the mine
    }
};
