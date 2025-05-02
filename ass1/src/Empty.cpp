#include "../include/BoardObject.h"

class Empty : public BoardObject {
private:
    // Private constructor to prevent instantiation
    Empty() : BoardObject(Point(0,0,GetBoardWidth(),GetBoardHight())) {}  // position doesn't matter for Empty
    static Empty* instance; // singleton pointer version


public:
    // Delete copy constructor and assignment
    Empty(const Empty&) = delete;
    Empty& operator=(const Empty&) = delete;

    // Static method to access the single instance
    static Empty& getInstance() {
        if (!instance)
            instance = new Empty();
        return *instance;
    }

    BoardObjectType getObjectType() const override {
        return BoardObjectType::Empty;
    }
    void destroyMyself() override {
        delete instance;
        instance = nullptr;
    }
};   
Empty* Empty::instance = nullptr;
