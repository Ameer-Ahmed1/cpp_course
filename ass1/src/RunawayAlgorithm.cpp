#include "../include/TankAlgorithm.h"
#include <algorithm>
#include <vector>
#include <string>

class RunAwayAlgorithm : public TankAlgorithm {
public:
    char decideAction(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) override {
        const int dangerRange = std::min(gameBoard.width, gameBoard.height) / 2;

        if (isInDanger(myTank, enemyTank, gameBoard, dangerRange)) {
            return findEscapePath(myTank, enemyTank, gameBoard);
        }

        if (isTargetShootable(myTank, enemyTank, gameBoard)) {
            return 'S';
        }

        return maintainSafeDistance(myTank, enemyTank, gameBoard, dangerRange);
    }

private:
    bool isInDanger(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard, int dangerRange) {
        if (calculateDistance(myTank.pos, enemyTank.pos, gameBoard) <= dangerRange) {
            return true;
        }

        for (const auto& shell : gameBoard.activeShells) {
            if (shell->tank.getId() != myTank.getId() &&
                calculateDistance(myTank.pos, shell->pos, gameBoard) <= dangerRange) {
                return true;
            }
        }
        return false;
    }

    bool isTargetShootable(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) {
        if (!myTank.canShoot()) return false;

        Point myPos = myTank.pos;
        Point enemyPos = enemyTank.pos;
        Direction dir = myTank.getDirection();

        if (!isInLineOfFire(myPos, enemyPos, dir, gameBoard)) return false;
        return !hasObstaclesInPath(myPos, enemyPos, dir, gameBoard);
    }

    char findEscapePath(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard) {
        std::vector<Point> threats;
        threats.push_back(enemyTank.pos);
        for (const auto& shell : gameBoard.activeShells) {
            if (shell->tank.getId() != myTank.getId()) {
                threats.push_back(shell->pos);
            }
        }

        Point escapeVector = Point(0, 0, gameBoard.width, gameBoard.height);
        Point myPos = myTank.pos;

        for (const auto& threat : threats) {
            int dx = threat.x - myPos.x;
            int dy = threat.y - myPos.y;
            if (dx > gameBoard.width / 2) dx -= gameBoard.width;
            if (dy > gameBoard.height / 2) dy -= gameBoard.height;
            escapeVector.x -= dx;
            escapeVector.y -= dy;
        }

        return getBestEscapeMove(myTank, escapeVector, gameBoard);
    }

    char getBestEscapeMove(const Tank& myTank, Point escapeVector, const GameBoard& gameBoard) {
        const Direction currentDir = myTank.getDirection();
        const Point myPos = myTank.pos;
        const int width = gameBoard.width;
        const int height = gameBoard.height;

        std::vector<std::pair<std::string, int>> moveScores;
        const std::vector<std::string> possibleMoves = {
            "F", "B", "L", "R", "U", "D", "UL", "UR", "DL", "DR"
        };

        for (const std::string& move : possibleMoves) {
            Point testPos = myPos;
            Direction moveDir = currentDir;

            if (move == "F") moveDir = currentDir;
            else if (move == "B") moveDir = oppositeDirection(currentDir);
            else moveDir = charToDirection(move);

            testPos.move(moveDir, width, height);
            testPos.x = (testPos.x + width) % width;
            testPos.y = (testPos.y + height) % height;

            BoardObjectType type = gameBoard.checkColl(testPos)->getObjectType();
            if (type != BoardObjectType::Empty || type == BoardObjectType::Wall || type == BoardObjectType::Mine) {
                continue;
            }

            Point moveDelta = Point(testPos.x - myPos.x, testPos.y - myPos.y, width, height);
            int score = moveDelta.x * escapeVector.x + moveDelta.y * escapeVector.y;
            moveScores.emplace_back(move, score);
        }

        if (!moveScores.empty()) {
            std::sort(moveScores.begin(), moveScores.end(),
                      [](const auto& a, const auto& b) { return a.second > b.second; });

            return moveScores[0].first[0]; // return first char of direction string (like 'U' or 'L')
        }

        return 'R';
    }

    char maintainSafeDistance(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard, int dangerRange) {
        int distance = calculateDistance(myTank.pos, enemyTank.pos, gameBoard);

        if (distance < dangerRange / 2) {
            return findEscapePath(myTank, enemyTank, gameBoard);
        } else if (distance > dangerRange * 1.5) {
            return getCautiousApproachMove(myTank, enemyTank, gameBoard);
        } else {
            return (rand() % 2) ? 'L' : 'R';
        }
    }

    int calculateDistance(Point a, Point b, const GameBoard& gameBoard) {
        int dx = std::min(abs(a.x - b.x), gameBoard.width - abs(a.x - b.x));
        int dy = std::min(abs(a.y - b.y), gameBoard.height - abs(a.y - b.y));
        return std::max(dx, dy);
    }

    Direction charToDirection(const std::string& move) {
        if (move == "U") return Direction::U;
        if (move == "UR") return Direction::UR;
        if (move == "R") return Direction::R;
        if (move == "DR") return Direction::DR;
        if (move == "D") return Direction::D;
        if (move == "DL") return Direction::DL;
        if (move == "L") return Direction::L;
        if (move == "UL") return Direction::UL;
        return Direction::U; // fallback
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
            default: return dir;
        }
    }

    bool isInLineOfFire(Point from, Point to, Direction dir, const GameBoard& gameBoard);
    bool hasObstaclesInPath(Point from, Point to, Direction dir, const GameBoard& gameBoard);
    char getCautiousApproachMove(const Tank& myTank, const Tank& enemyTank, const GameBoard& gameBoard);
};
