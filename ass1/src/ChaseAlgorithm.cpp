#include "TankAlgorithm.cpp"  // Base class interface
#include "GameBoard.cpp"      // For GameBoard reference
#include "Tank.cpp"           // For Tank class
#include "Point.h"
#include <cmath>            // For abs() function

class ChaseAlgorithm : public TankAlgorithm {
public:
    char decideAction(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) override {
        // If we can shoot the enemy, do it
        if (canShootEnemy(myTank, enemyTank, gameBoard)) {
            return 'S'; // Shoot
        }

        // Otherwise move toward enemy using BFS pathfinding
        return findPathToEnemy(myTank, enemyTank, gameBoard);
    }

private:
   bool ChaseAlgorithm::canShootEnemy(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) {
    // Get positions and direction
    Point myPos = myTank.getPosition();
    Point enemyPos = enemyTank.getPosition();
    Direction dir = myTank.getDirection();
    int width = gameBoard.getWidth();
    int height = gameBoard.getHeight();

    // Calculate optimal shooting distance (half of smallest board dimension)
    int optimalDistance = std::min(width, height) / 2;

    // Calculate actual distance with wrap-around
    int dx = std::min(abs(enemyPos.x - myPos.x), width - abs(enemyPos.x - myPos.x));
    int dy = std::min(abs(enemyPos.y - myPos.y), height - abs(enemyPos.y - myPos.y));
    int actualDistance = std::max(dx, dy); // Using chessboard distance

    if (!myTank.canShoot()) {
        return false;
    }

    // Check if enemy is within optimal range
    if (actualDistance > optimalDistance) {
        return false;
    }

    // Check if enemy is in line of fire
    if (!isInLineOfFire(myPos, enemyPos, dir, width, height)) {
        return false;
    }
    
    // Check for walls in the path
    return !hasObstaclesInPath(myPos, enemyPos, dir, gameBoard);
}

bool ChaseAlgorithm::isInLineOfFire(const Point& myPos, const Point& enemyPos, Direction dir, 
                                   int width, int height) {
    // Handle different directions
    switch (dir) {
        case Direction::UP:
            return myPos.x == enemyPos.x && 
                   (myPos.y >= enemyPos.y || (myPos.y == 0 && enemyPos.y == height-1));
        case Direction::DOWN:
            return myPos.x == enemyPos.x && 
                   (myPos.y <= enemyPos.y || (myPos.y == height-1 && enemyPos.y == 0));
        case Direction::LEFT:
            return myPos.y == enemyPos.y && 
                   (myPos.x >= enemyPos.x || (myPos.x == 0 && enemyPos.x == width-1));
        case Direction::RIGHT:
            return myPos.y == enemyPos.y && 
                   (myPos.x <= enemyPos.x || (myPos.x == width-1 && enemyPos.x == 0));
        // Diagonal cases
        case Direction::UP_LEFT:
            return checkDiagonalLine(myPos, enemyPos, -1, -1, width, height);
        case Direction::UP_RIGHT:
            return checkDiagonalLine(myPos, enemyPos, 1, -1, width, height);
        case Direction::DOWN_LEFT:
            return checkDiagonalLine(myPos, enemyPos, -1, 1, width, height);
        case Direction::DOWN_RIGHT:
            return checkDiagonalLine(myPos, enemyPos, 1, 1, width, height);
        default:
            return false;
    }
}

bool ChaseAlgorithm::checkDiagonalLine(const Point& start, const Point& end, 
                                      int dx, int dy, int width, int height) {
    // Check if points lie on a diagonal line with given dx/dy step
    Point current = start;
    while (true) {
        if (current == end) return true;
        
        // Move to next point with wrap-around
        current.x = (current.x + dx + width) % width;
        current.y = (current.y + dy + height) % height;
        
        // If we've wrapped all the way around without finding the target
        if (current == start) return false;
    }
}

bool ChaseAlgorithm::hasObstaclesInPath(const Point& start, const Point& end, 
                                       Direction dir, const GameBoard& gameBoard) {
    int width = gameBoard.getWidth();
    int height = gameBoard.getHeight();
    
    // Get step directions based on tank's facing
    int dx = 0, dy = 0;
    switch (dir) {
        case Direction::UP: dy = -1; break;
        case Direction::DOWN: dy = 1; break;
        case Direction::LEFT: dx = -1; break;
        case Direction::RIGHT: dx = 1; break;
        case Direction::UP_LEFT: dx = -1; dy = -1; break;
        case Direction::UP_RIGHT: dx = 1; dy = -1; break;
        case Direction::DOWN_LEFT: dx = -1; dy = 1; break;
        case Direction::DOWN_RIGHT: dx = 1; dy = 1; break;
    }
    
    Point current = start;
    while (true) {
        // Move to next point
        current.x = (current.x + dx + width) % width;
        current.y = (current.y + dy + height) % height;
        
        // Stop when we reach enemy position
        if (current == end) return false;
        
        // Check for walls or other obstacles
        if (gameBoard.isWall(current.x, current.y)) {
            return true;
        }
        
        // If we've wrapped all the way around (shouldn't happen if enemy is in line)
        if (current == start) return true;
    }
}

char ChaseAlgorithm::findPathToEnemy(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) {
    const int width = gameBoard.getWidth();
    const int height = gameBoard.getHeight();
    Point start = myTank.getPosition();
    Point target = enemyTank.getPosition();
    Direction currentDir = myTank.getDirection();

    // Collision check using Tank's method
    if (start == target) return 'X';

    // BFS initialization
    std::queue<Point> q;
    std::unordered_map<Point, Point, PointHash> came_from;
    std::unordered_map<Point, char, PointHash> first_move;
    std::unordered_set<Point, PointHash> visited;

    q.push(start);
    visited.insert(start);
    came_from[start] = start;
    first_move[start] = '\0';

    // Movement options using Tank's relative directions
    const std::vector<std::pair<Direction, char>> direction_moves = {
        {Direction::U, 'U'},    // Up
        {Direction::UR, 'UR'},  // Up-Right
        {Direction::R, 'R'},    // Right
        {Direction::DR, 'DR'},  // Down-Right
        {Direction::D, 'D'},    // Down
        {Direction::DL, 'DL'},  // Down-Left
        {Direction::L, 'L'},    // Left
        {Direction::UL, 'UL'},  // Up-Left
        {Direction::U, 'F'},    // Forward (using current direction)
        {Direction::D, 'B'}     // Backward
    };

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        for (const auto& [moveDir, moveCmd] : direction_moves) {
            Point newPos = current;
            
            // Calculate new position using Tank's movement logic
            if (moveCmd == 'F') {
                newPos.move(currentDir, width, height);
            } 
            else if (moveCmd == 'B') {
                newPos.move(oppositeDirection(currentDir), width, height);
            }
            else {
                newPos.move(moveDir, width, height);
            }

            // Normalize position for wrap-around
            newPos.x = (newPos.x + width) % width;
            newPos.y = (newPos.y + height) % height;

            // Skip if invalid position
            if (visited.count(newPos) || 
                !gameBoard.isEmpty(newPos.x, newPos.y) || 
                gameBoard.isWall(newPos.x, newPos.y) || 
                gameBoard.isMine(newPos.x, newPos.y)) {
                continue;
            }

            // Record path
            came_from[newPos] = current;
            first_move[newPos] = (current == start) ? moveCmd : first_move[current];
            visited.insert(newPos);

            // Found target
            if (newPos == target) {
                // Reconstruct path to find first move
                Point path_step = newPos;
                while (came_from[path_step] != start) {
                    path_step = came_from[path_step];
                }
                return first_move[path_step];
            }

            q.push(newPos);
        }
    }

    // Fallback behavior - use Tank's relative movement
    return getSafeRelativeMove(myTank, gameBoard);
}

// Helper functions
Direction oppositeDirection(Direction dir) {
    return static_cast<Direction>((static_cast<int>(dir) + 4) % 8);
}

char getSafeRelativeMove(const Tank& tank, const GameBoard& gameBoard) {
    const int width = gameBoard.getWidth();
    const int height = gameBoard.getHeight();
    Point current = tank.getPosition();
    Direction dir = tank.getDirection();

    // Check forward first
    Point forwardPos = current;
    forwardPos.move(dir, width, height);
    forwardPos.x = (forwardPos.x + width) % width;
    forwardPos.y = (forwardPos.y + height) % height;
    
    if (gameBoard.isEmpty(forwardPos.x, forwardPos.y) && 
        !gameBoard.isWall(forwardPos.x, forwardPos.y) && 
        !gameBoard.isMine(forwardPos.x, forwardPos.y)) {
        return 'F';
    }

    // Check rotations in order of preference
    for (char rot : {'R', 'L', 'UR', 'UL', 'DR', 'DL', 'U', 'D'}) {
        Direction newDir = dir;
        if (rot == 'R') newDir = Direction::R;
        else if (rot == 'L') newDir = Direction::L;
        // ... other direction conversions
        
        Point testPos = current;
        testPos.move(newDir, width, height);
        testPos.x = (testPos.x + width) % width;
        testPos.y = (testPos.y + height) % height;
        
        if (gameBoard.isEmpty(testPos.x, testPos.y) && 
            !gameBoard.isWall(testPos.x, testPos.y) && 
            !gameBoard.isMine(testPos.x, testPos.y)) {
            return rot;
        }
    }

    // Last resort - backward
    Point backwardPos = current;
    backwardPos.move(oppositeDirection(dir), width, height);
    backwardPos.x = (backwardPos.x + width) % width;
    backwardPos.y = (backwardPos.y + height) % height;
    
    if (gameBoard.isEmpty(backwardPos.x, backwardPos.y) && 
        !gameBoard.isWall(backwardPos.x, backwardPos.y) && 
        !gameBoard.isMine(backwardPos.x, backwardPos.y)) {
        return 'B';
    }

    // If completely blocked, rotate right
    return 'R';
}
};