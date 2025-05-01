#pragma once
#include "BoardObject.h"
#include "Point.h"
#include "Enums.h"
#include <tuple>

class Shell;
class GameBoard;
class GameManager;

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
    int backwardWaitTime;
    bool waitingBackward;
    int id;

    /**
     * @brief Handles collision logic with another object.
     * @param object The object the tank would collide with.
     * @return ID of the winner (1 or 2), 0 if invalid move, -1 if nothing, -2 if both lose.
     */
    int collidedWithObject(BoardObject& object);

    /**
     * @brief Executes the real movement and board update if the move is valid.
     * @param newpos The new position to move to.
     * @param oldpos The current position before moving.
     * @return Same return value logic as collidedWithObject().
     */
    int applyMovement(std::tuple<Point, Point> movement);

public:
    /**
     * @brief Constructor for Tank.
     * @param p Initial position.
     * @param direction Initial direction.
     * @param shells Initial number of shells.
     * @param tankId Player ID (1 or 2).
     */
    Tank(Point p, Direction direction, int shells, int tankId);

    /// @return The current direction of the tank.
    Direction getDirection() const;
    bool canmove(){
         return(waitingBackward&&(waitingTime>0));
    }
    /// @return Number of remaining shells.
    int getRemainingShells() const;

    /// @return Time left before tank can act again.
    int getWaitingTime() const;

    /// @return Player ID of the tank (1 or 2).
    int getId() const;

    /// @return True if the tank has at least one shell.
    bool hasShellsRemaining() const;

    /// Decrease remaining shells by 1.
    void decreaseShells();

    /// Set the waiting time to a specific value.
    void setWaitingTime(int time);

    /// Reset shooting cooldown to max.
    void resetShootingTime();

    /// Set whether the last action was backward.
    void setLastAction(bool action);

    /// @return True if the last action was backward.
    bool getLastAction() const;

    /// @return Current shooting cooldown.
    int getShootingTime() const;

    /// Decrease the shooting cooldown by 1.
    void decreaseShootingTime();

    /// @return True if tank can shoot (cooldown is 0 and has shells).
    bool canShoot() const;

    /**
     * @brief Attempts to move the tank forward.
     * @return A tuple with (new position, previous position).
     */
    std::tuple<Point, Point> moveForward();

    /**
     * @brief Handles the tank's backward move behavior (delayed or instant).
     * @return A tuple with (new position, previous position).
     */
    std::tuple<Point, Point> moveBackward();

    /**
     * @brief Sets the tank's new direction (if not waiting).
     * @param newDir The new direction to face.
     */
    void rotate(Direction newDir);

    /**
     * @brief Fires a shell if possible.
     * @param gameManager Reference to the GameManager for shell tracking.
     * @param otherTank Reference to the opponent tank.
     * @return True if the shell was successfully fired.
     */
    bool shoot(GameManager& gameManager, Tank* otherTank);

    /// @return BoardObjectType::Tank
    BoardObjectType getObjectType() const override;

    /**
     * @brief Destroys the tank and removes it from the board.
     */
    void destroyMyself() override;
};
