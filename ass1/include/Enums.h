#pragma once

// Enum for actions a tank can take
enum class Action {
    F,    // Move Forward
    B,    // Move Backward
    R8L,  // Rotate 1/8 Left
    R8R,  // Rotate 1/8 Right
    R4L,  // Rotate 1/4 Left
    R4R,  // Rotate 1/4 Right
    SHOOT // Shoot
};

// Enum for rotation values (how much the tank rotates)
enum class Rotation {
    ONE_EIGHT_R = 1,  // 1/8 Right (value = 1)
    ONE_QUARTER_R = 2,  // 1/4 Right (value = 2)
    ONE_EIGHT_L = -1,   // 1/8 Left (value = -1)
    ONE_QUARTER_L = -2  // 1/4 Left (value = -2)
};

// Enum for directions (tank facing directions)
enum class Direction {
    L = 6,  // Left (value = 6)
    R = 2,  // Right (value = 2)
    U = 0,  // Up (value = 0)
    D = 4,  // Down (value = 4)
    UR = 1, // Up-Right (value = 1)
    DR = 3, // Down-Right (value = 3)
    DL = 5, // Down-Left (value = 5)
    UL = 7  // Up-Left (value = 7)
};


enum class BoardObjectType {
    Empty,
    Wall,
    Tank,
    Shell,
    Mine
};