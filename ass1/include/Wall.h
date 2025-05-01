#pragma once
#include "BoardObject.h"
#include "Empty.h"  // Needed for destroyMyself()

class Wall : public BoardObject {
private:
    int life;

public:
    // Constructor
    Wall(Point p);

    // Accessors and modifiers
    int getLife() const;
    void decreaseLife();
    bool isDestroyed() const;

    // Overrides
    BoardObjectType getObjectType() const override;
    void destroyMyself() override;
};
