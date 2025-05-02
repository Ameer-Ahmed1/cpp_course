//
// Created by Admin on 5/2/2025.
//


#pragma once
#include "Point.h"
#include "Enums.h"
#include "GameBoard.h"


class BoardObject {
public:
    static GameBoard* board;
    Point pos;

    BoardObject(Point p) : pos(p) {}

public:
    virtual ~BoardObject() = default;
    virtual BoardObjectType getObjectType() const = 0;
    virtual void destroyMyself() = 0;
    static BoardObject* checkColl(Point p); //givin point return whats in that point

    static void setGameBoard(GameBoard* gb){board = gb;}
    static int GetBoardWidth(){return board->width;}
    static int GetBoardHight(){return board->height;}
};



