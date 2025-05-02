#pragma once
#include <vector>
class BoardObject;
class Shell;
#include <Point.h>
#include <Empty.h>


class GameBoard {
public:
    int width;
    int height;
    std::vector<std::vector<BoardObject*>> matrix;
    std::vector<Shell*> inactiveShells;
    std::vector<Shell*> activeShells;

    GameBoard(int w, int h)
        : width(w),
          height(h),
          matrix(w, std::vector<BoardObject*>(h, &Empty::getInstance())),
          inactiveShells(),
          activeShells() {}

    BoardObject*  checkColl (Point  p) const; //givin point return whats in that point
    void updateGameBoard(BoardObject* obj, int x, int y);
    void addInactiveShell(Shell* shell);
    void clearInactiveShells();
    void addActiveShells(Shell* shell);
    void clearBoard();
};
