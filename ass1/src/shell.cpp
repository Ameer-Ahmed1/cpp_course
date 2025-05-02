#include "../include/BoardObject.h"
#include "Tank.h"  // since no Tank.h
#include "Empty.h"  // since no Tank.h
#include "Wall.h"  // since no Tank.h


enum class Direction;  // forward declaration

class Shell : public BoardObject {
private:
    Tank& tank;         // The tank that fired the shell
    Direction dir;      // Direction of movement

public:
    Shell(Point p, Tank& t, Direction d): BoardObject(p), tank(t), dir(d) {}


    BoardObjectType getObjectType() const override {
        return BoardObjectType::Shell;
    }

    //return the id of tank that win or -1(nothing happpend)or -2 if both lose
    int moveShell() {
        for (int i =0 ; i<2 ; i++){//moving 2 steps
            pos.move(dir,GetBoardWidth(),GetBoardHight());
            BoardObject* collidedObject = checkColl(pos);
            if (collidedObject->getObjectType() != BoardObjectType::Empty ||collidedObject->getObjectType() != BoardObjectType::Mine){
                return collidedWithObject(*collidedObject);}
        }
        return -1;
    }

    void destroyMyself() override {//dosent delete from ram 
        board->matrix[pos.x][pos.y] = &Empty::getInstance();
        board->addInactiveShell(this);
        
    }

    int collidedWithObject(BoardObject& object) {// Return value: winner's ID (1 or 2), 0 for invalid move, or -1 if nothing happens or -2 both loos.
        BoardObjectType type = object.getObjectType();
        switch (type) {
            case BoardObjectType::Shell: {
                destroyMyself();
                object.destroyMyself();
                return -1;} 
            case BoardObjectType::Tank: {
                int id = static_cast<Tank&>(object).getId();
                return (id == 1) ? 2 : 1;}
            case BoardObjectType::Wall: {
                Wall& wall = static_cast<Wall&>(object);
                wall.decreaseLife();
                if (wall.isDestroyed()) {wall.destroyMyself();}
                destroyMyself();
                return -1;
            }
            default: {return -1;}// Nothing happens
        }
    }
};
