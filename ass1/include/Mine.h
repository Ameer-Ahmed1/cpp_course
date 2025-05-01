#pragma once
#include "BoardObject.h"
#include "Empty.h"

class Mine : public BoardObject {
private:
    bool active;

public:
    Mine(Point p, bool isActive);

    bool isActive() const;
    void deactivate();
    void activate();

    void destroyMyself() override;
    BoardObjectType getObjectType() const override;
};
