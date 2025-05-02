//
// Created by Admin on 5/2/2025.
//

#ifndef BOARDOBJECT_H
#define BOARDOBJECT_H

#pragma once
#include "Point.h"
#include "Enums.h"

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



#endif //BOARDOBJECT_H
