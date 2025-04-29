class RunAwayAlgorithm : public TankAlgorithm {
public:
    char decideAction(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) override {
        // If enemy is far and we can shoot safely, do it
        if (isSafeToShoot(myTank, enemyTank, gameBoard)) {
            return 'S';
        }

        // Otherwise move away from enemy
        return findEscapePath(myTank, enemyTank, gameBoard);
    }

private:
    bool isSafeToShoot(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) {
        // Check if we can shoot without being in immediate danger
        // Returns true if it's safe to shoot now
        return false; // Placeholder
    }

    char findEscapePath(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) {
        // Move in opposite direction from enemy
        int dx = enemyTank.getX() - myTank.getX();
        int dy = enemyTank.getY() - myTank.getY();
        
        // Simple approach - move away from enemy
        if (abs(dx) > abs(dy)) {
            return (dx > 0) ? 'L' : 'R'; // Rotate away
        } else {
            return (dy > 0) ? 'U' : 'D'; // Rotate away
        }
        
        // Note: A more sophisticated approach would consider walls and mines
    }
};

// GameManager would use these algorithms like:
// TankAlgorithm* player1Algo = new ChaseAlgorithm();
// TankAlgorithm* player2Algo = new RunAwayAlgorithm();
// char action = currentPlayerAlgo->decideAction(myTank, enemyTank, gameState);