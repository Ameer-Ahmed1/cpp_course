#include <vector>
#include <queue>
#include <utility> // for pair
#include <algorithm>

// Forward declarations
class Tank;
class GameBoard;

// Base Algorithm Interface
class TankAlgorithm {
public:
    virtual ~TankAlgorithm() = default;
    virtual char decideAction(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) = 0;
};



// RunAway Algorithm - tries to evade enemy tank and fire when safe
