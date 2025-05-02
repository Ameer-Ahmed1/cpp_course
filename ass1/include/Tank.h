#pragma once
#include "BoardObject.h"
#include "Point.h"
#include "Enums.h"
#include <tuple>


/**
 * @brief Represents a controllable tank on the game board.
 */
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

    /**
     * @brief Handles collision logic with another object.
     * @param object The object the tank would collide with.
     * @return ID of the winner (1 or 2), 0 if invalid move, -1 if nothing, -2 if both lose.
     */
    int collidedWithObject(BoardObject& object);

    /**
     * @brief Executes the real movement and board update if the move is valid.
     * @param movement A tuple of (new position, old position).
     * @return Same return value logic as collidedWithObject().
     */
    int applyMovement(std::tuple<Point, Point> movement);

public:
    /** Constructor */
    Tank(Point p, Direction direction, int shells, int tankId);

    Direction getDirection() const;
    int getRemainingShells() const;
    int getId() const;
    bool hasShellsRemaining() const;
    void decreaseShells();
    void resetShootingTime();
    void setLastAction(bool action);
    bool getLastAction() const;
    bool getwaitingBackward() const;
    void setwaitingBackward(bool a);
    int getShootingTime() const;
    int getbackwardWaitTime() const;
    void setbackwardWaitTime(int t);
    void decreaseShootingTime();
    void decreaseWaitingTime();
    bool canShoot() const;
    int moveForward();
    bool timeToMoveF();
    int moveBackward();
    bool rotate(Direction newDir);
    bool shoot();
    BoardObjectType getObjectType() const override;
    /** Remove tank from board */
    void destroyMyself() override;
};
