#pragma once
#include <vector>
#include "BoardObject.h"
#include "Shell.h" 

class GameBoard {
public:
    int width;
    int height;
    std::vector<std::vector<BoardObject*>> matrix;
    std::vector<Shell*> inactiveShells; // NEW vector to hold inactive shells

    GameBoard(int w, int h) : width(w), height(h), matrix(w, std::vector<BoardObject*>(h, nullptr)) {}

    void updateGameBoard(BoardObject* obj, int x, int y) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            matrix[x][y] = obj;
        }
    }

    //add shell to inactiveShells
    void addInactiveShell(Shell* shell) {
        inactiveShells.push_back(shell);
    }

    // delete all shells in inactiveShells
    void clearInactiveShells() {
        for (Shell* shell : inactiveShells) {
            delete shell;
        }
        inactiveShells.clear();
    }
};
