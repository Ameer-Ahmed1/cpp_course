#include "../include/Tank.h"
#include "../include/Shell.h"
#include "../include/Empty.h"

Tank::Tank(Point p, Direction direction, int shells, int tankId)
    : BoardObject(p), dir(direction), lastAction(false),
      waitingTime(0), shootingTime(0), remainingShells(shells), id(tankId) {}

Direction Tank::getDirection() const { return dir; }
int Tank::getRemainingShells() const { return remainingShells; }
int Tank::getId() const { return id; }
bool Tank::hasShellsRemaining() const { return remainingShells > 0; }
void Tank::decreaseShells() { remainingShells--; }
void Tank::resetShootingTime() { shootingTime = 4; }
void Tank::setLastAction(bool action) { lastAction = action; }
bool Tank::getLastAction() const { return lastAction; }
bool Tank::getwaitingBackward() const { return waitingBackward; }
void Tank::setwaitingBackward(bool a) { waitingBackward = a; }
int Tank::getShootingTime() const { return shootingTime; }
int Tank::getbackwardWaitTime() const { return backwardWaitTime; }
void Tank::setbackwardWaitTime(int t) { backwardWaitTime = t; }
void Tank::decreaseShootingTime() { if (shootingTime > 1) shootingTime--; }
void Tank::decreaseWaitingTime() { if (backwardWaitTime > 1) backwardWaitTime--; }

bool Tank::canShoot() const {
    return shootingTime == 0 && remainingShells > 0;
}

int Tank::moveForward() {
    Point newPos = pos;
    newPos.move(dir, GetBoardWidth(),   GetBoardHight());
    return applyMovement(std::make_tuple(newPos, pos));
}

bool Tank::timeToMoveF() {
    return waitingBackward && backwardWaitTime == 0;
}

int Tank::moveBackward() {
    waitingBackward = false;
    Point newPos = pos;
    newPos.moveBack(dir, GetBoardWidth(),   GetBoardHight());
    lastAction = true;
    return applyMovement(std::make_tuple(newPos, pos));
}

bool Tank::rotate(Direction newDir) {
    if (waitingBackward) return false;
    dir = newDir;
    return true;
}

bool Tank::shoot() {
    if (!canShoot() || waitingBackward) return false;
    Shell* shell = new Shell(Point(pos.x, pos.y, board->getHeight(), board->getWidth()), *this, dir);
    board->addActiveShells(shell);
    decreaseShells();
    resetShootingTime();
    return true;
}

BoardObjectType Tank::getObjectType() const {
    return BoardObjectType::Tank;
}

void Tank::destroyMyself() {
    board->matrix[pos.x][pos.y] = &Empty::getInstance();
    delete this;
}

int Tank::collidedWithObject(BoardObject& object) {
    BoardObjectType type = object.getObjectType();
    switch (type) {
        case BoardObjectType::Shell:
        case BoardObjectType::Mine:
            return (id == 1) ? 2 : 1;
        case BoardObjectType::Tank:
            return -2;
        case BoardObjectType::Wall:
            return 0;
        default:
            return -1;
    }
}

int Tank::applyMovement(std::tuple<Point, Point> movement) {
    Point oldPos = std::get<1>(movement);
    Point newPos = std::get<0>(movement);

    BoardObject* obj = board->checkColl(newPos);
    int result = collidedWithObject(*obj);

    if (result == -1) {
        board->updateGameBoard(&Empty::getInstance(), oldPos.x, oldPos.y);
        board->updateGameBoard(this, newPos.x, newPos.y);
        pos = newPos;
    }

    return result;
}
