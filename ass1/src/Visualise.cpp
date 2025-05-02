#include <SFML/Graphics.hpp>
#include "../include/Tank.h"
#include "../include/Shell.h"
#include "../include/Wall.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tank Battle");

    // Load textures
    sf::Texture tankTexture;
    tankTexture.loadFromFile("tank.png"); 

    sf::Sprite tankSprite(tankTexture);
    
    // Create your game objects
    Tank playerTank(100, 100); // Example initialization
    Shell shell(200, 200);      // Example shell
    Wall wall(300, 150);        // Example wall

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update tank position from game class
        tankSprite.setPosition(playerTank.getX(), playerTank.getY());

        // Clear and draw game objects
        window.clear();
        window.draw(tankSprite);
        // You can draw walls and shells in a similar manner
        window.display();
    }

    return 0;
}
