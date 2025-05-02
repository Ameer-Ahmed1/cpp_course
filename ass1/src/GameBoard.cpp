#pragma once
#include <vector>
#include "BoardObject.h"
#include "Shell.h"
#include <algorithm>
#include <Empty.h>

class GameBoard {
public:
    int width;
    int height;
    std::vector<std::vector<BoardObject*>> matrix;
    std::vector<Shell*> inactiveShells; // vector to hold inactive shells
    std::vector<Shell*> activeShells;
    GameBoard(int w, int h) : width(w), height(h), matrix(w, std::vector<BoardObject*>(h, nullptr)) {}

    void updateGameBoard(BoardObject* obj, int x, int y) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            matrix[x][y] = obj;
        }
    }
     BoardObject*  checkColl (Point p)const { //givin point return whats in that point
        return (matrix[p.x][p.y]);
    }


    //add shell to inactiveShells
    void addInactiveShell(Shell* shell) {
        // 1. Add to inactiveShells
        inactiveShells.push_back(shell);

        // 2. Remove from activeShells
        auto it = std::find(activeShells.begin(), activeShells.end(), shell);
        if (it != activeShells.end()) {
            activeShells.erase(it);
        }
    }

    // delete all shells in inactiveShells
    void clearInactiveShells() {
        for (Shell* shell : inactiveShells) {
            delete shell;
        }
        inactiveShells.clear();
    }
    void addActiveShells(Shell* shell) {
        activeShells.push_back(shell);
    }
    void clearBoard() {
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                if (matrix[x][y] != &Empty::getInstance()) {
                    delete matrix[x][y];
                    matrix[x][y] = &Empty::getInstance();
                }
            }
        }
    }





    
};
