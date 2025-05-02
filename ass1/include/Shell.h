#pragma once
#include "BoardObject.h"
#include "Enums.h"


class Shell : public BoardObject {
public:
    Tank& tank;         // The tank that fired the shell
    Direction dir;      // Direction of movement

public:
    Shell(Point p, Tank& t, Direction d);

    BoardObjectType getObjectType() const override;
    int moveShell();
    void destroyMyself() override;
    int collidedWithObject(BoardObject& object);
};
