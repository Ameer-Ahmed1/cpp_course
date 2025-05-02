#include "../include/BoardObject.h"
#include "../include/GameBoard.h"

GameBoard* BoardObject::board = nullptr;

BoardObject* BoardObject::checkColl(Point p) {
    return board->matrix[p.x][p.y];
}
