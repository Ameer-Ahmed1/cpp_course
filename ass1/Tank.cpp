#include "BoardObject.h"
#include <vector>

enum class Direction;  // Forward declaration
class Shell;           // Forward declaration

class Tank : public BoardObject {
private:
    Direction dir;
    bool lastAction;
    int waitingTime;     // 0, 1, or 2
    int shootingTime;
    int remainingShells;
    std::vector<Shell*> activeShells;

public:
    Tank(Point p, Direction direction, int shells)
        : BoardObject(p), dir(direction), lastAction(false),
          waitingTime(0), shootingTime(0), remainingShells(shells) {}

    void somePureVirtualFunction() override {
        // Empty implementation for now
    }

    void moveForward() {
        // TODO: Implement movement logic
    }

    void moveBackward() {
        // TODO: Implement movement logic
    }

    void rotate() {
        // TODO: Implement rotation logic
    }

    bool shoot() {
        // TODO: Use shell if available
        return false;
    }

    bool checkRemaining() const {
        return remainingShells > 0;
    }

    Direction getDirection() const {
        return dir;
    }

    int getRemainingShells() const {
        return remainingShells;
    }

    int getWaitingTime() const {
        return waitingTime;
    }

    const std::vector<Shell*>& getActiveShells() const {
        return activeShells;
    }
};
