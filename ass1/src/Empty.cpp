#include "BoardObject.h"

class Empty : public BoardObject {
private:
    // Private constructor to prevent instantiation
    Empty() : BoardObject(Point(0, 0)) {}  // position doesn't matter for Empty

public:
    // Delete copy constructor and assignment
    Empty(const Empty&) = delete;
    Empty& operator=(const Empty&) = delete;

    // Static method to access the single instance
    static Empty& getInstance() {
        static Empty instance;
        return instance;
    }

    void somePureVirtualFunction() override {
        // No behavior
    }
};