//
// Created by Admin on 5/2/2025.
//

#ifndef RUNAWAYALGORITHM_H
#define RUNAWAYALGORITHM_H

#endif //RUNAWAYALGORITHM_H
#include <TankAlgorithm.h>
class RunAwayAlgorithm : public TankAlgorithm {
public:
    char decideAction(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) override;

private:
    bool isInDanger(const Tank&, const Tank&, const GameBoard&, int);
    bool isTargetShootable(const Tank&, const Tank&, const GameBoard&);
    char findEscapePath(const Tank&, const Tank&, const GameBoard&);
    char getBestEscapeMove(const Tank&, Point, const GameBoard&);
    char maintainSafeDistance(const Tank&, const Tank&, const GameBoard&, int);
    int calculateDistance(Point, Point, const GameBoard&);
    Direction charToDirection(char move);
    bool isInLineOfFire(Point, Point, Direction, const GameBoard&);
    bool hasObstaclesInPath(Point, Point, Direction, const GameBoard&);
};