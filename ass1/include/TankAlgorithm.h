#include <vector>
#include <queue>
#include <utility> // for pair
#include <algorithm>
#include "Tank.h"
#include "GameBoard.h"

// Base Algorithm Interface

class TankAlgorithm {
public:
    virtual ~TankAlgorithm() = default;
    virtual char decideAction(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) = 0;
};
