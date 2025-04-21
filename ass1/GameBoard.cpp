#pragma once
#include <vector>
#include "BoardObject.h"

class GameBoard {
public:
    int width;
    int height;
    std::vector<std::vector<BoardObject*>> matrix;  // Use pointers for dynamic polymorphism

    GameBoard(int w, int h) : width(w), height(h), matrix(w, std::vector<BoardObject*>(h, nullptr)) {}

    void updateGameBoard(BoardObject* obj, int x, int y) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            matrix[x][y] = obj;
        }
    }
};
