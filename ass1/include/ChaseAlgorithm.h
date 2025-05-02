//
// Created by Admin on 5/2/2025.
//

#ifndef CHASEALGORITHM_H
#define CHASEALGORITHM_H

#endif //CHASEALGORITHM_H
#pragma once

#include "TankAlgorithm.h"
#include "Point.h"
#include "../include/GameBoard.h"
#include "../include/Tank.h"



class ChaseAlgorithm : public TankAlgorithm {
public:
    char decideAction(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) override;

private:
    bool canShootEnemy(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard);
    bool isInLineOfFire(const Point& myPos, const Point& enemyPos, Direction dir, int width, int height);
    bool hasObstaclesInPath(const Point& start, const Point& end, Direction dir, const GameBoard& gameBoard);
    char findPathToEnemy(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard);
    bool checkDiagonalLine(const Point& start, const Point& end,int dx, int dy, int width, int height);
};
