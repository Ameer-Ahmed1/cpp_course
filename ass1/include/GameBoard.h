#pragma once
#include <vector>
#include <algorithm>
#include "BoardObject.h"
#include "Shell.h"  // Include the header, not Shell.cpp
#include "Empty.h"  // For clearBoard() fallback

class GameBoard {
public:
    int width;
    int height;
    std::vector<std::vector<BoardObject*>> matrix;
    std::vector<Shell*> inactiveShells;
    std::vector<Shell*> activeShells;

    GameBoard(int w, int h);

    void updateGameBoard(BoardObject* obj, int x, int y);
    void addInactiveShell(Shell* shell);
    void clearInactiveShells();
    void addActiveShells(Shell* shell);
    void clearBoard();
};
