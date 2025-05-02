#pragma once
#include "Enums.h"

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
