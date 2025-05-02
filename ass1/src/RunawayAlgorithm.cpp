#include "../include/TankAlgorithm.h"

class RunAwayAlgorithm : public TankAlgorithm {
public:
    char decideAction(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) override {
        // Calculate danger threshold (half of smallest board dimension)
        const int dangerRange = std::min(gameBoard.width, gameBoard.height) / 2;
        
        // Check for immediate threats (tank or shells in danger range)
        if (isInDanger(myTank, enemyTank, gameBoard, dangerRange)) {
            // Flee from nearest threat
            return findEscapePath(myTank, enemyTank, gameBoard);
        }
        
        // If safe and enemy is in line of fire, shoot
        if (isTargetShootable(myTank, enemyTank, gameBoard)) {
            return 'S';
        }
        
        // Default cautious behavior
        return maintainSafeDistance(myTank, enemyTank, gameBoard, dangerRange);
    }

private:
    bool isInDanger(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard, int dangerRange) {
        // Check enemy tank proximity
        if (calculateDistance(myTank.pos, enemyTank.pos, gameBoard) <= dangerRange) {
            return true;
        }
        
        // Check for incoming shells
        for (const auto& shell : gameBoard.activeShells) {
            if (shell->tank.getId() != myTank.getId() && // Enemy shell
                calculateDistance(myTank.pos, shell->pos, gameBoard) <= dangerRange) {
                return true;
            }
        }
        return false;
    }

    bool isTargetShootable(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) {
        // Can't shoot if on cooldown or no ammo
        if (!myTank.canShoot()) return false;
        
        // Check if enemy is in line of fire
        Point myPos = myTank.pos;
        Point enemyPos = enemyTank.pos;
        Direction dir = myTank.getDirection();
        
        // Verify line of sight
        if (!isInLineOfFire(myPos, enemyPos, dir, gameBoard)) {
            return false;
        }
        
        // Check path is clear
        return !hasObstaclesInPath(myPos, enemyPos, dir, gameBoard);
    }

    char findEscapePath(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) {
        // Get all threats (enemy tank + shells)
        std::vector<Point> threats;
        threats.push_back(enemyTank.pos);
        for (const auto& shell : gameBoard.activeShells) {
            if (shell->tank.getId() != myTank.getId()) {
                threats.push_back(shell->pos);
            }
        }
        
        // Calculate escape vector (away from all threats)
        Point escapeVector = Point(0, 0,gameBoard.width,gameBoard.height);
        Point myPos = myTank.pos;
        for (const auto& threat : threats) {
            int dx = threat.x - myPos.x;
            int dy = threat.y - myPos.y;
            
            // Normalize for wrap-around
            if (dx > gameBoard.width/2) dx -= gameBoard.width;
            if (dy > gameBoard.height/2) dy -= gameBoard.height;
            
            escapeVector.x -= dx;
            escapeVector.y -= dy;
        }
        
        // Find safest available move
        return getBestEscapeMove(myTank, escapeVector, gameBoard);
    }

    char getBestEscapeMove(const Tank& myTank, Point escapeVector, const GameBoard& gameBoard) {
        const Direction currentDir = myTank.getDirection();
        const Point myPos = myTank.pos;
        const int width = gameBoard.width;
        const int height = gameBoard.height;
        
        // Prioritize moves that align with escape vector
        std::vector<std::pair<char, int>> moveScores;
        
        // Evaluate all possible moves
        const std::vector<char> possibleMoves = {'F', 'B', 'L', 'R', 'U', 'D','UL', 'UR', 'DL', 'DR'};
        
        for (char move : possibleMoves) {
            Point testPos = myPos;
            Direction moveDir = currentDir;
            
            // Calculate move direction
            if (move == 'F') moveDir = currentDir;
            else if (move == 'B') moveDir = oppositeDirection(currentDir);
            else moveDir = charToDirection(move);
            
            // Calculate new position
            testPos.move(moveDir, width, height);
            testPos.x = (testPos.x + width) % width;
            testPos.y = (testPos.y + height) % height;
            
            // Skip invalid positions
            if (!((gameBoard.checkColl(testPos))->getObjectType() == BoardObjectType::Empty) ||
                (gameBoard.checkColl(testPos))->getObjectType() == BoardObjectType::Wall||
                (gameBoard.checkColl(testPos))->getObjectType() == BoardObjectType::Mine) {
                continue;
            }
            
            // Calculate move score (alignment with escape vector)
            Point moveDelta = Point(testPos.x - myPos.x, testPos.y - myPos.y,gameBoard.height,gameBoard.width);
            int score = moveDelta.x * escapeVector.x + moveDelta.y * escapeVector.y;
            moveScores.emplace_back(move, score);
        }
        
        // Select best scoring valid move
        if (!moveScores.empty()) {
            std::sort(moveScores.begin(), moveScores.end(), 
                [](const auto& a, const auto& b) { return a.second > b.second; });
            return moveScores[0].first;
        }
        
        // If no valid moves, rotate as last resort
        return 'R';
    }

    char maintainSafeDistance(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard, int dangerRange) {
        // Default cautious movement pattern
        int distance = calculateDistance(myTank.pos, enemyTank.pos, gameBoard);
        
        if (distance < dangerRange/2) {
            // Too close - create more distance
            return findEscapePath(myTank, enemyTank, gameBoard);
        } else if (distance > dangerRange*1.5) {
            // Too far - consider approaching carefully
            return getCautiousApproachMove(myTank, enemyTank, gameBoard);
        } else {
            // Maintain position - small random movement
            return (rand() % 2) ? 'L' : 'R';
        }
    }

    // Helper functions
    int calculateDistance(Point a, Point b, const GameBoard& gameBoard) {
        int dx = std::min(abs(a.x - b.x), gameBoard.width - abs(a.x - b.x));
        int dy = std::min(abs(a.y - b.y), gameBoard.height - abs(a.y - b.y));
        return std::max(dx, dy); // Chessboard distance
    }
    
    Direction charToDirection(char move) {
        // Convert move char to Direction enum
        // Implementation depends on your Direction enum
    }
    
    bool isInLineOfFire(Point from, Point to, Direction dir, const GameBoard& gameBoard) {
        // Implementation of line-of-sight check
    }
    
    bool hasObstaclesInPath(Point from, Point to, Direction dir, const GameBoard& gameBoard) {
        // Implementation of path clearance check
    }
    Direction oppositeDirection(Direction dir) {
        switch (dir) {
            case Direction::U:  return Direction::D;
            case Direction::UR: return Direction::DL;
            case Direction::R:  return Direction::L;
            case Direction::DR: return Direction::UL;
            case Direction::D:  return Direction::U;
            case Direction::DL: return Direction::UR;
            case Direction::L:  return Direction::R;
            case Direction::UL: return Direction::DR;
            default:            return dir; // fallback, shouldn't happen
        }
    }
};