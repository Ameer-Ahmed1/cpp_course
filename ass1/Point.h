#pragma once

class Point {
public:
    int x, y;

    // Ensures point fits within a matrix of size width x height
    Point(int x_val, int y_val, int width, int height) {
        x = (x_val % width + width) % width;
        y = (y_val % height + height) % height;
    }
};
