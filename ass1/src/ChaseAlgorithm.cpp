#include <ChaseAlgorithm.h>
#include <queue>
#include <unordered_set>

// If we can shoot the enemy, do it
char ChaseAlgorithm::decideAction(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) {
    if (canShootEnemy(myTank, enemyTank, gameBoard)) {
        return 'S'; // Shoot
    }

    // Otherwise move toward enemy using BFS pathfinding
    return findPathToEnemy(myTank, enemyTank, gameBoard);
}

bool ChaseAlgorithm::canShootEnemy(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) {
    // Get positions and direction
    Point myPos = myTank.pos;
    Point enemyPos = enemyTank.pos;
    Direction dir = myTank.getDirection();
    int width = gameBoard.width;
    int height = gameBoard.height;

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
        case Direction::U:
            return myPos.x == enemyPos.x &&
                   (myPos.y >= enemyPos.y || (myPos.y == 0 && enemyPos.y == height - 1));
        case Direction::D:
            return myPos.x == enemyPos.x &&
                   (myPos.y <= enemyPos.y || (myPos.y == height - 1 && enemyPos.y == 0));
        case Direction::L:
            return myPos.y == enemyPos.y &&
                   (myPos.x >= enemyPos.x || (myPos.x == 0 && enemyPos.x == width - 1));
        case Direction::R:
            return myPos.y == enemyPos.y &&
                   (myPos.x <= enemyPos.x || (myPos.x == width - 1 && enemyPos.x == 0));
        // Diagonal cases
        case Direction::UL:
            return checkDiagonalLine(myPos, enemyPos, -1, -1, width, height);
        case Direction::UR:
            return checkDiagonalLine(myPos, enemyPos, 1, -1, width, height);
        case Direction::DL:
            return checkDiagonalLine(myPos, enemyPos, -1, 1, width, height);
        case Direction::DR:
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
    int width = gameBoard.width;
    int height = gameBoard.height;

    // Get step directions based on tank's facing
    int dx = 0, dy = 0;
    switch (dir) {
        case Direction::U: dy = -1; break;
        case Direction::D: dy = 1; break;
        case Direction::L: dx = -1; break;
        case Direction::R: dx = 1; break;
        case Direction::UL: dx = -1; dy = -1; break;
        case Direction::UR: dx = 1; dy = -1; break;
        case Direction::DL: dx = -1; dy = 1; break;
        case Direction::DR: dx = 1; dy = 1; break;
    }

    Point current = start;
    while (true) {
        // Move to next point
        current.x = (current.x + dx + width) % width;
        current.y = (current.y + dy + height) % height;

        // Stop when we reach enemy position
        if (current == end) return false;

        // Check for walls or other obstacles
        if ((gameBoard.checkColl(current))->getObjectType() == BoardObjectType::Wall) {
            return true;
        }

        // If we've wrapped all the way around (shouldn't happen if enemy is in line)
        if (current == start) return true;
    }
}

char ChaseAlgorithm::findPathToEnemy(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) {
    const int width = gameBoard.width;
    const int height = gameBoard.height;
    Point start = myTank.pos;
    Point target = enemyTank.pos;
    Direction currentDir = myTank.getDirection();

    // Collision check using Tank's method
    if (target == start) return 'X';

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
        {Direction::U, 'U'}, {Direction::UR, 'R'}, {Direction::R, 'R'},
        {Direction::DR, 'R'}, {Direction::D, 'D'}, {Direction::DL, 'L'},
        {Direction::L, 'L'}, {Direction::UL, 'L'}
    };

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        for (const auto& [moveDir, moveCmd] : direction_moves) {
            Point newPos = current;
            newPos.move(moveDir, width, height);
            newPos.x = (newPos.x + width) % width;
            newPos.y = (newPos.y + height) % height;

            if (visited.count(newPos) ||
                (gameBoard.checkColl(newPos)->getObjectType() != BoardObjectType::Empty)) {
                continue;
            }

            came_from[newPos] = current;
            first_move[newPos] = (current == start) ? moveCmd : first_move[current];
            visited.insert(newPos);

            if (newPos == target) {
                Point step = newPos;
                while (came_from[step] != start) {
                    step = came_from[step];
                }
                return first_move[step];
            }

            q.push(newPos);
        }
    }

    return 'R'; // fallback if no path
}

// Helper functions outside class
Direction oppositeDirection(Direction dir) {
    return static_cast<Direction>((static_cast<int>(dir) + 4) % 8);
}

char getSafeRelativeMove(const Tank& tank, const GameBoard& gameBoard) {
    const int width = gameBoard.width;
    const int height = gameBoard.height;
    Point current = tank.pos;
    Direction dir = tank.getDirection();

    // Check forward first
    Point forwardPos = current;
    forwardPos.move(dir, width, height);
    forwardPos.x = (forwardPos.x + width) % width;
    forwardPos.y = (forwardPos.y + height) % height;

    if ((gameBoard.checkColl(forwardPos))->getObjectType() == BoardObjectType::Empty) {
        return 'F';
    }

    // Check rotations in order of preference
    for (char rot : {'R', 'L', 'U', 'D'}) {
        Direction newDir = dir;
        if (rot == 'R') newDir = Direction::R;
        else if (rot == 'L') newDir = Direction::L;
        else if (rot == 'U') newDir = Direction::U;
        else if (rot == 'D') newDir = Direction::D;

        Point testPos = current;
        testPos.move(newDir, width, height);
        testPos.x = (testPos.x + width) % width;
        testPos.y = (testPos.y + height) % height;

        if ((gameBoard.checkColl(testPos))->getObjectType() == BoardObjectType::Empty) {
            return rot;
        }
    }

    // Last resort - backward
    Point backwardPos = current;
    backwardPos.move(oppositeDirection(dir), width, height);
    backwardPos.x = (backwardPos.x + width) % width;
    backwardPos.y = (backwardPos.y + height) % height;

    if ((gameBoard.checkColl(backwardPos))->getObjectType() == BoardObjectType::Empty) {
        return 'B';
    }

    return 'R';
}