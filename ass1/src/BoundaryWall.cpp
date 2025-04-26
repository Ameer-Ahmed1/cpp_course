#include "Wall.cpp"

class BoundaryWall : public Wall {
public:
    BoundaryWall(Point p) : Wall(p) {}

    std::string getWallType() const override {
        return "BoundaryWall";
    }
};
