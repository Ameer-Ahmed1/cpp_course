#pragma once
#include "Point.h"
#include "Enums.h"

class GameBoard;  // Forward declaration
static GameBoard* board;

class BoardObject {
protected:
    Point pos;  // Position of the object
    BoardObject(Point p) : pos(p) {}

public:
    virtual ~BoardObject() = default;
    virtual void onCollideWithShell() = 0;
    virtual BoardObjectType getObjectType() const = 0; // PURE VIRTUAL function

    static *BoardObject checkColl(Point pos) { //givin point return whats in that point
        return board->matrix[p.x][p.y]; 
    }
    static void setGameBoard(GameBoard* gb) {
        board = gb;
    }
    static int GetBoardWidth() {
        return board.width;
    }
    static int GetBoardHight() {
        return board.height;
    }

};
