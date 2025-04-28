#include "BoardObject.h"
#include <vector>

// enum class Direction {
//     U = 0,
//     UR = 1,
//     R = 2,
//     DR = 3,
//     D = 4,
//     DL = 5,
//     L = 6,
//     UL = 7
// };

class Shell;
class GameBoard;
class GameManager; // Forward declaration needed for interaction

class Tank : public BoardObject {
private:
    Direction dir;
    bool lastAction;
    int waitingTime;
    int shootingTime;
    int remainingShells;
    std::vector<Shell*> activeShells;
    int id;
    int handleColl(Point pos){
       /* BoardObject* collidedObject = checkColl(pos);
        switch (collidedObject->getObjectType()) {
            case BoardObjectType::Empty:
                return -1;  // Can step into empty space
            case BoardObjectType::Mine:
                return this.id;  // the looser one
    
            case BoardObjectType::Wall:
                return 0; illegal
    
            case BoardObjectType::Tank:
                return 3 ; 
            case BoardObjectType::Shell:
                return this.id;  // Can move into a shell spot (optional - depends on your game logic)
        }*/
    
    }

public:
    Tank(Point p, Direction direction, int shells, int tankId)
        : BoardObject(p), dir(direction), lastAction(false),
          waitingTime(0), shootingTime(0), remainingShells(shells), id(tankId) {}

    void somePureVirtualFunction() override {}

    Direction getDirection() const { return dir; }
    int getRemainingShells() const { return remainingShells; }
    int getWaitingTime() const { return waitingTime; }
    int getId() const { return id; }

    // Tank actions now only *request* a change.  The GameManager will apply it.
    Point moveForward();
    Point moveBackward();
    void rotate(Direction newDir);
    bool shoot(GameManager& gameManager, Tank* otherTank); // Pass GameManager
    void removeShell(Shell* shell);  // delete from the activeShells
    bool checkRemaining() const {
        return remainingShells > 0;
    }

    void decreaseShells() {
        remainingShells--;
    }

    void setWaitingTime(int time) {
        waitingTime = time;
    }

    void resetShootingTime() {
        shootingTime = 4;
    }

    void setLastAction(bool action) {
        lastAction = action;
    }

    bool getLastAction() const {
        return lastAction;
    }

    int getShootingTime() const{
        return shootingTime;
    }

    void decreaseShootingTime(){
        shootingTime--;
    }
    BoardObjectType getObjectType() const override {
        return BoardObjectType::Tank;
    }
};

// Tank class method implementations

Point Tank::moveForward() {
    if (waitingTime > 0) return pos; // Return current position if waiting

    Point newPos = pos;
    newPos.move(dir,GetBoardWidth(),GetBoardHight());
    //checking for coll
    checkColl(Point pos) ;
    result = handleColl(pos);
    return newPos; // Return the *desired* new position
}

Point Tank::moveBackward() {
    if (waitingTime > 0) return pos;
    if (!lastAction) {
        waitingTime = 2;
        lastAction = true;
        return pos; // Return current position, no move yet
    }

    Point newPos = pos;

    switch (dir) {
        case Direction::U:    newPos.y++; break;
        case Direction::UR:   newPos.x--; newPos.y++; break;
        case Direction::R:    newPos.x--; break;
        case Direction::DR:   newPos.x--; newPos.y--; break;
        case Direction::D:    newPos.y--; break;
        case Direction::DL:   newPos.x++; newPos.y--; break;
        case Direction::L:    newPos.x++; break;
        case Direction::UL:   newPos.x++; newPos.y++; break;
    }
    waitingTime = 0;
    return newPos;
}

void Tank::rotate(Direction newDir) {
    if (waitingTime > 0) return;
    dir = newDir;
}

bool Tank::shoot(GameManager& gameManager, Tank* otherTank) { // Pass GameManager
    if (shootingTime > 0 || remainingShells <= 0) return false;

    // Create a new shell.  The GameManager will manage its lifetime.
    Shell* shell = new shell(Point(pos.x, pos.y), *this, dir, 2);
    gameManager.addShell(shell); // Add to GameManager's shell list
    remainingShells--;
    shootingTime = 4;
    return true;
}
int onCollideWithShell() override {
    return id;
}

void Tank::removeShell(Shell* shell) {
    auto it = std::find(activeShells.begin(), activeShells.end(), shell);
    if (it != activeShells.end()) {
        delete *it;
        activeShells.erase(it);
    }
}


