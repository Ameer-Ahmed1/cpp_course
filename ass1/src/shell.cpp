#include "BoardObject.h"
#include "Tank.cpp"  // since no Tank.h
#include <iostream>  // optional for debugging

enum class Direction;  // forward declaration

class Shell : public BoardObject {
private:
    Tank& tank;         // The tank that fired the shell
    Direction dir;      // Direction of movement
    bool shouldBeDestroyed = false;

public:
    Shell(Point p, Tank& t, Direction d)
        : BoardObject(p), tank(t), dir(d) {}


    void onCollideWithShell() override {
        return 0;
    }
    BoardObjectType getObjectType() const override {
        return BoardObjectType::Shell;
    }

    //return 0(the collied object has to be deleted) or the id of tank that loss or -1(nothing happpend)
    int moveShell() {
        int retval ;
        for (int i =0 ; i<2 ; i++){//moving 2 steps
            pos.move(dir,GetBoardWidth(),GetBoardHight());
            BoardObject* collidedObject = checkColl(pos);
            if (collidedObject != &Empty::getInstance()) {// It’s an Empty object
                shouldBeDestroyed = true;  // Mark yourself
                result = collidedObject.onCollideWithShell();
                if (result == 0){//	The collided object must be deleted. 
                    collidedObject.destroymyself(); 
                    result = -1
                }
                return result                                   
            }
        }
        return -1;
    }

    void destroyMyself() {
        auto it = std::find(tank.activeShells.begin(), tank.activeShells.end(), this);
        if (it != tank.activeShells.end()) {
            tank.activeShells.erase(it);
        }
        delete this;
    }
};
