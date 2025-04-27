#pragma once
#include "Enums.h"

class Point {
public:
    int x, y;

    Point(int x_val, int y_val, int width, int height) {
        x = (x_val % width + width) % width;
        y = (y_val % height + height) % height;
    }

    void move(Direction dir, int width, int height) {
        switch (dir) {
            case Direction::U:  y--; break;
            case Direction::UR: x++; y--; break;
            case Direction::R:  x++; break;
            case Direction::DR: x++; y++; break;
            case Direction::D:  y++; break;
            case Direction::DL: x--; y++; break;
            case Direction::L:  x--; break;
            case Direction::UL: x--; y--; break;
            default: break;
        }
        x = (x % width + width) % width;
        y = (y % height + height) % height;
    }
    

    void moveBack(Direction dir, int width, int height) {
        switch (dir) {
            case Direction::U:  y++; break;
            case Direction::UR: x--; y++; break;
            case Direction::R:  x--; break;
            case Direction::DR: x--; y--; break;
            case Direction::D:  y--; break;
            case Direction::DL: x++; y--; break;
            case Direction::L:  x++; break;
            case Direction::UL: x++; y++; break;
            default: break;
        }
        x = (x % width + width) % width;
        y = (y % height + height) % height;
    }
};
