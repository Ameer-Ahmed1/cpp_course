#include "../include/BoardObject.h"
#include <Empty.h>


class Mine : public BoardObject {
private:

public:
    Mine(Point p)
        : BoardObject(p){}

    void destroyMyself() override {
        board->matrix[pos.x][pos.y] = &Empty::getInstance();
        delete this;
    }
    BoardObjectType getObjectType() const override {
        return BoardObjectType::Mine;
    }

};
