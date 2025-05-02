#include "Shell.h"
#include "Tank.h"
#include "Empty.h"
#include "Wall.h"
#include "BoardObject.h"
// Constructor
Shell::Shell(Point p, Tank& t, Direction d)
    : BoardObject(p), tank(t), dir(d) {}

// Return the type of this object
BoardObjectType Shell::getObjectType() const {
    return BoardObjectType::Shell;
}

// Move the shell up to 2 steps forward
//return the id of tank that win or -1(nothing happpend)or -2 if both lose
int Shell::moveShell() {
    for (int i = 0; i < 2; i++) {
        pos.move(dir, GetBoardWidth(), GetBoardHight());
        BoardObject* collidedObject = checkColl(pos);
        if (collidedObject->getObjectType() != BoardObjectType::Empty &&
            collidedObject->getObjectType() != BoardObjectType::Mine) {
            return collidedWithObject(*collidedObject);
            }
    }
    return -1;
}

// Mark the shell as destroyed
void Shell::destroyMyself() {
    board->matrix[pos.x][pos.y] = &Empty::getInstance();
    board->addInactiveShell(this);
}

// Handle collision
int Shell::collidedWithObject(BoardObject& object) {
    BoardObjectType type = object.getObjectType();
    switch (type) {
        case BoardObjectType::Shell:
            destroyMyself();
            object.destroyMyself();
            return -1;

        case BoardObjectType::Tank: {
            int id = static_cast<Tank&>(object).getId();
            object.destroyMyself();
            destroyMyself();
            return (id == 1) ? 2 : 1;
        }

        case BoardObjectType::Wall: {
            Wall& wall = static_cast<Wall&>(object);
            wall.decreaseLife();
            if (wall.isDestroyed()) {
                wall.destroyMyself();
            }
            destroyMyself();
            return -1;
        }

        default:
            return -1;
    }
}
