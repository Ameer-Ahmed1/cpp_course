#include "Tank.h"
#include "GameBoard.h"
#pragma once

// Base Algorithm Interface

class TankAlgorithm {
public:
    virtual ~TankAlgorithm() = default;
    virtual char decideAction(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) = 0;
};
