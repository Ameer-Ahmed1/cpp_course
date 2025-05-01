#pragma once
#include "BoardObject.h"

class Empty : public BoardObject {
private:
    Empty();  // Private constructor
    static Empty* instance;

public:
    Empty(const Empty&) = delete;
    Empty& operator=(const Empty&) = delete;

    static Empty& getInstance();
    BoardObjectType getObjectType() const override;
    void destroyMyself() override;
};
