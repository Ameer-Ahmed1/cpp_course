#pragma once
#include "BoardObject.h"
#include "Empty.h"
#include "Enums.h"  // for Direction
class Tank;         // Forward declaration

class Shell : public BoardObject {
private:
    Tank& tank;         // The tank that fired the shell
    Direction dir;      // Direction of movement

public:
    Shell(Point p, Tank& t, Direction d);

    BoardObjectType getObjectType() const override;
    int moveShell();
    void destroyMyself() override;
    int collidedWithObject(BoardObject& object) override;
};
