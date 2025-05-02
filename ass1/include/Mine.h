#pragma once
#include "BoardObject.h"
#include "Empty.h"

class Mine : public BoardObject {
private:

public:
    Mine(Point p);


    void destroyMyself() override;
    BoardObjectType getObjectType() const override;
};
