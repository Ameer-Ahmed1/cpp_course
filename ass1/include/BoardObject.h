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
    virtual void somePureVirtualFunction() = 0;

    static bool checkColl(const BoardObject& a, const BoardObject& b) {//givin object
        return (a.pos.x == b.pos.x && a.pos.y == b.pos.y);
    }
    static *BoardObject checkColl(Point pos) { //givin point return whats in that point
        return get_boardobj(pos);

    }

    static void setGameBoard(GameBoard* gb) {
        board = gb;
    }
    static *BoardObject get_boardobj(Point p) {
        return  board->matrix[p.x][p.y]; 
    }

    static int GetBoardWidth() {
        return board.width;
    }
    static int GetBoardHight() {
        return board.height;
    }

};
