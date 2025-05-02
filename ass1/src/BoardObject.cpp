//
// Created by Admin on 5/2/2025.
//

#include "../include/BoardObject.h"
#include "../include/GameBoard.h"

// Definition of static member
GameBoard* BoardObject::board = nullptr;

// Constructor definition
BoardObject::BoardObject(Point p) : pos(p) {}

static BoardObject* checkColl(Point p) { //givin point return whats in that point
    return (board->checkColl(p));
}
// Static method implementations
void BoardObject::setGameBoard(GameBoard* gb) {
    board = gb;
}

int BoardObject::GetBoardWidth() {
    return board->width;
}

int BoardObject::GetBoardHight() {
    return board->height;
}
