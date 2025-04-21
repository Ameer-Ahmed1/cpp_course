#include "Wall.cpp"  // or use Wall.h if you split it later

class InnerWall : public Wall {
public:
    InnerWall(Point p) : Wall(p) {}

    std::string getWallType() const override {
        return "InnerWall";
    }
};