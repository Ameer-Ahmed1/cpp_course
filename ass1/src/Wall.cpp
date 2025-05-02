#include "../include/BoardObject.h"
#include <Empty.h>


class Wall : public BoardObject {
private:
    int life;
public:
    Wall(Point p) : BoardObject(p),life(2) {}
    int getLife() const {
        return life;
    }

    void decreaseLife() {
        if (life > 0) {
            life--;
        }
    }

    bool isDestroyed() const {
        return life <= 0;
    }

    //return 0 if has to be deletd, return -1 if nothing happend

    /*int collidedWithObject(BoardObject& object) override {// Return value: winner's ID (1 or 2), 0 for invalid move, or -1 if nothing happens.
        BoardObjectType type = object.getObjectType();
        switch (type) {
            case BoardObjectType::Tank: {return 0;}
            case BoardObjectType::Shell: {
                decreaseLife();
                if (isDestroyed()) {}
                }
            default: {return -1;}
        }
    }*/
    BoardObjectType getObjectType() const override {
        return BoardObjectType::Wall;
    }
    void destroyMyself() override {
        board->matrix[pos.x][pos.y] = &Empty::getInstance();
        delete this;
    }

};
