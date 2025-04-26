#include "Wall.cpp"  // or use Wall.h if you split it later

class InnerWall : public Wall {
private:
    int life;

public:
    InnerWall(Point p) : Wall(p), life(2) {}

    std::string getWallType() const override {
        return "InnerWall";
    }

    int getLife() const {
        return life;
    }

    void decreaseLife() {
        if (life > 0) {
            life--;
        }
    }

    bool isDestroyed() const {
        return life <= 0;
    }
};
