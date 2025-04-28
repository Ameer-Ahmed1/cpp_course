#include "BoardObject.h"
#include <iostream>

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
    void onCollideWithShell() override {
        decreaseLife();
        if (isDestroyed()) {
            return 0; 
        }
        return -1;
    }
    BoardObjectType getObjectType() const override {
        return BoardObjectType::Wall;
    }

};
