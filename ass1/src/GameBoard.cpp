
#include "GameBoard.h"
#include "Shell.h"

BoardObject* GameBoard::checkColl(Point p) const {
    return matrix[p.x][p.y];
}

void GameBoard::updateGameBoard(BoardObject* obj, int x, int y) {
    matrix[x][y] = obj;
}

void GameBoard::addInactiveShell(Shell* shell) {
    inactiveShells.push_back(shell);
}

void GameBoard::clearInactiveShells() {
    for (Shell* shell : inactiveShells) {
        delete shell;
    }
    inactiveShells.clear();
}

void GameBoard::addActiveShells(Shell* shell) {
    activeShells.push_back(shell);
}

void GameBoard::clearBoard() {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (matrix[x][y] != &Empty::getInstance()) {
                matrix[x][y]->destroyMyself();
                matrix[x][y] = &Empty::getInstance();
            }
        }
    }
    }


