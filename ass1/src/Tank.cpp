#include "BoardObject.h"
#include "Shell.h"
#include "GameBoard.h"
#include "GameManager.h"
#include "Empty.h"
#include <vector>
#include <tuple>

class Tank : public BoardObject {
private:
    Direction dir;
    bool lastAction;
    int waitingTime;
    int shootingTime;
    int remainingShells;
    int backwardWaitTime = 0;
    bool waitingBackward = false;
    int id;

    int collidedWithObject(BoardObject& object) {
        BoardObjectType type = object.getObjectType();
        switch (type) {
            case BoardObjectType::Shell:
            case BoardObjectType::Mine:
                return (id == 1) ? 2 : 1;
            case BoardObjectType::Tank:
                return -2;  // both lose
            case BoardObjectType::Wall:
                return 0;   // invalid move
            default:
                return -1;  // no collision
        }
    }

    int applyMovement(std::tuple<Point, Point> movement) {
        Point oldPos = std::get<1>(movement);
        Point newPos = std::get<0>(movement);
    
        BoardObject* obj = board->checkColl(newPos);
        int result = collidedWithObject(*obj);
    
        if (result == -1) {  // move is allowed
            board->updateGameBoard(&Empty::getInstance(), oldPos.x, oldPos.y);
            board->updateGameBoard(this, newPos.x, newPos.y);
            pos = newPos;
        }
    
        return result;
    }
    

public:
    Tank(Point p, Direction direction, int shells, int tankId)
        : BoardObject(p), dir(direction), lastAction(false),
          waitingTime(0), shootingTime(0), remainingShells(shells), id(tankId) {}


    Direction getDirection() const { return dir; }
    int getRemainingShells() const { return remainingShells; }
    int getId() const { return id; }
    bool hasShellsRemaining() const { return remainingShells > 0; }
    void decreaseShells() { remainingShells--; }
    void resetShootingTime() { shootingTime = 4; }
    void setLastAction(bool action) { lastAction = action; }
    bool getLastAction() const { return lastAction; }
    bool getwaitingBackward() const {return waitingBackward; }
    void setwaitingBackward(bool a) const {waitingBackward = a ; }
    int getShootingTime() const { return shootingTime; }
    int getbackwardWaitTime() const { return backwardWaitTime; }
    void setbackwardWaitTime(int t) {backwardWaitTime = t; }
    void decreaseShootingTime() { if (shootingTime >1){shootingTime--;} }
    void decreaseWaitingTime() { if (backwardWaitTime >1){backwardWaitTime--;} }


    bool canShoot() const {
        return shootingTime == 0 && remainingShells > 0;
    }

    int moveForward() {
        Point newPos = pos;
        newPos.move(dir, GetBoardWidth(), GetBoardHeight());
        return applyMovement(std::make_tuple(newPos, pos));
    }

    bool timeToMoveF(){
        if (waitingBackward && backwardWaitTime ==0){return true;} 
        return false;
    }

    int moveBackward() {
        waitingBackward = false;
        Point newPos = pos;
        newPos.moveBack(dir, GetBoardWidth(), GetBoardHeight());
        lastAction = true;
        return applyMovement(std::make_tuple(newPos, pos));
    }

    bool rotate(Direction newDir) {
        if (waitingBackward) return false;
        dir = newDir;
        return true;
    }

    bool shoot() {
        if (!canShoot() || waitingBackward) return false;
        Shell* shell = new Shell(Point(pos.x, pos.y), *this, dir);
        board->addActiveShells(shell);
        decreaseShells();
        resetShootingTime();
        return true;
    }

    BoardObjectType getObjectType() const override {
        return BoardObjectType::Tank;
    }

    void destroyMyself() override {
        board->matrix[pos.x][pos.y] = &Empty::getInstance();
        delete this;
    }
};
