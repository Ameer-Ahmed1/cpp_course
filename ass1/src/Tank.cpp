#include "BoardObject.h"
#include <vector>
#include <tuple>
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
    int backwardWaitTime = 0;
    bool waitingBackward = false;
    //std::vector<Shell*> activeShells;
    int id;
    int collidedWithObject(BoardObject& object) {// Return value: winner's ID (1 or 2), 0 for invalid move, or -1 if nothing happens or -2 both loos.
        BoardObjectType type = object.getObjectType();
        switch (type) {
            case BoardObjectType::Shell: {return (id == 1) ? 2 : 1;} // If tank 1 hits shell, tank 2 wins, and vice versa
            case BoardObjectType::Tank: {return -2;}// both lose
            case BoardObjectType::Mine: {return (id == 1) ? 2 : 1;}
            case BoardObjectType::Wall: {return 0;}  
            default: {return -1;}// Nothing happens
        }
    }
    int realMov(Point newpos,Point oldpos){
        int res;
        BoardObject* collidedObject = board->checkColl(newPos);
        res = collidedWithObject(collidedObject);
        if (res == -1){//we can move
            board->updateGameBoard(&Empty::getInstance(),oldpos.x,oldpos.y);
            board->pdateGameBoard(this,newpos.x,newpos.y);
            this.pos = newpos;
        }
        return res ;
    }
    

public:
    Tank(Point p, Direction direction, int shells, int tankId)
        : BoardObject(p), dir(direction), lastAction(false),
          waitingTime(), shootingTime(0), remainingShells(shells), id(tankId) {}

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
    //void removeShell(Shell* shell);  // delete from the activeShells
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
    void destroyMyself() override {
        /*for (Shell* shell : activeShells) {
            shell->destroyMyself(); // Let each shell clean itself
        }
        activeShells.clear();*/
    
        board->matrix[pos.x][pos.y] = &Empty::getInstance();
    
        delete this;
    }
    
};

// Tank class method implementations

std::tuple<Point,Point> Tank::moveForward() {
    int res ;
    if (waitingBackward) {
        waitingBackward = false ;
        //return -1; //cancel the backword
        return make_tuple(pos,pos);
        }
    Point newPos = pos;
    newPos.move(dir,GetBoardWidth(),GetBoardHeight());
    //return realmov(newPos,pos); // Return the *desired* new position
    return make_tuple(newPos,pos);
}



std::tuple<Point,Point> Tank::MoveBackward() {
    if (waitingBackward) {
        if (backwardWaitTime > 0)// {return -1;}// Still waiting, nothing happens
        { return make_tuple(pos,pos);}
        else {// Now perform the backward move
            Point newPos = pos;
            newPos.moveBack(dir,GetBoardWidth(),GetBoardHight());
            waitingBackward = false;
            //return realmov(newPos,pos);
            lastAction = true;/////////////////////false elsewhere
            return make_tuple(newPos,pos);
        }
    }
    // If no backward waiting yet, start new backward request
    if (lastAction){//the last action was backword
        Point newPos = pos;
        newPos.moveBack(dir,GetBoardWidth(),GetBoardHight());
        return make_tuple(newPos,pos);
        //return realmov(newPos,pos)
    }
    waitingBackward = true;
    backwardWaitTime = 2;
    return make_tuple(pos,pos);
    //return -1; // Stay in place for now
}

void Tank::rotate(Direction newDir) {
    if (waitingTime > 0) return;
    dir = newDir;
}

bool Tank::canShoot() const {
    return shootingTime == 0 && remainingShells > 0;
}

bool Tank::shoot(GameManager& gameManager, Tank* otherTank) {
    if (!canShoot()) return false;
    // Create a new shell. The GameManager will manage its lifetime.
    Shell* shell = new Shell(Point(pos.x, pos.y), *this, dir);
    board->addActiveShells(shell); // Add to GameManager's shell list
    remainingShells--;
    shootingTime = 4;
    return true;
}



/*void Tank::removeShell(Shell* shell) {
    auto it = std::find(activeShells.begin(), activeShells.end(), shell);
    if (it != activeShells.end()) {
        delete *it;
        activeShells.erase(it);
    }
}*/

=

