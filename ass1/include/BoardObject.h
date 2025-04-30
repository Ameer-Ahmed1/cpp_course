#pragma once
#include "Point.h"
#include "Enums.h"

class GameBoard;  // Forward declaration

class BoardObject {
protected:
    static GameBoard* board;
    Point pos;  // Position of the object
    BoardObject(Point p) : pos(p) {}
    

public:
    virtual ~BoardObject() = default;
    virtual BoardObjectType getObjectType() const = 0; // PURE VIRTUAL function
    virtual void destroyMyself() = 0;

    static *BoardObject checkColl(Point p) { //givin point return whats in that point
        return board->matrix[p.x][p.y]; 
    }
    static void setGameBoard(GameBoard* gb) {
        board = gb;
    }
    static int GetBoardWidth() {
        return board->width;
    }
    static int GetBoardHight() {
        return board.height;
    }

};
