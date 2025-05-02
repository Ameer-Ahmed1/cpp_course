#pragma once
#include "BoardObject.h"

/**
 * @brief Represents a shell fired by a tank, moving in a given direction.
 */
class Shell : public BoardObject {
public:
    Tank& tank;         // The tank that fired this shell
    Direction dir;      // Direction the shell is moving

    Shell(Point p, Tank& t, Direction d);
    BoardObjectType getObjectType() const override;
    int moveShell();
    void destroyMyself() override;
    int collidedWithObject(BoardObject& object);
};
