#include "../include/Empty.h"

Empty* Empty::instance = nullptr;

Empty::Empty() : BoardObject(Point(0, 0, board->width(), board->height)) {}

Empty& Empty::getInstance() {
    if (!instance)
        instance = new Empty();
    return *instance;
}

BoardObjectType Empty::getObjectType() const {
    return BoardObjectType::Empty;
}

void Empty::destroyMyself() {
    delete instance;
    instance = nullptr;
}
