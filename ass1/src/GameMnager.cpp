#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class GameManager {
private:
    int looser = -1;
    tank& tank1 ;
    tank& tank2 ;

public:
    GameManager() = default;
    
    void initalization(const std::string& filePath) {
        GameBoard* initialization(const std::string& filePath) {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                std::cerr << "Error: Cannot open file " << filePath << std::endl;
                return nullptr;
            }
        
            int width, height;
            file >> width >> height;
        
            GameBoard* board = new GameBoard(width, height); // Create the board inside function
        
            // Fill all cells with Empty
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    board->matrix[i][j] = &Empty::getInstance();
                }
            }
        
            std::string line;
            std::getline(file, line); // move to next line after width height
        
            int tankCount = 0;
        
            while (std::getline(file, line)) {
                if (line.empty()) continue;
        
                std::istringstream iss(line);
                std::string type;
                int x, y;
        
                iss >> type >> x >> y;
        
                if (x < 0 || x >= width || y < 0 || y >= height) {
                    std::cerr << "Warning: Object at (" << x << "," << y << ") is out of bounds, ignored." << std::endl;
                    continue;
                }
        
                if (type == "tank") {
                    if (tankCount >= 2) {
                        std::cerr << "Error: More than 2 tanks defined!" << std::endl;
                        delete board;
                        return nullptr;
                    }
                    Tank* tank = new Tank(Point(x, y), (tankCount == 0 ? Direction::L : Direction::R), 16, tankCount + 1);
                    board->matrix[x][y] = tank;
                    if tankCount == 0{tank = tank1;}
                    else{tank = tank2;}
                    tankCount++;  // First tank gets id=1, second gets id=2
                }
                else if (type == "mine") {
                    Mine* mine = new Mine(Point(x, y));
                    board->matrix[x][y] = mine;
                }
                else if (type == "wall") {
                    Wall* wall = new Wall(Point(x, y));
                    board->matrix[x][y] = wall;
                }
                else {
                    std::cerr << "Warning: Unknown object type '" << type << "', ignored." << std::endl;
                }
            }
        
            if (tankCount != 2) {
                std::cerr << "Error: Must have exactly 2 tanks! Found " << tankCount << std::endl;
                delete board;
                return nullptr;
            }
        
            return board; // Return the board
        }        
    }

    void start(){
        int steps = 40
        while (getSteps()>0){

             // --- 1. Move tank1 shells ---
            for (auto it = tank1->shells.begin(); it != tank1->shells.end(); ) {
                Shell* shell = *it;
                int looser = shell->moveShell();
                if (looser == 1 || looser == 2) {
                    break;
                }

                if (shell->shouldBeDestroyed) {
                    shell->destroyMyself();
                } 
                else {
                    ++it;
                }
            }
            // --- 1. Move tank2 shells ---
            for (auto it = tank2->shells.begin(); it != tank2->shells.end(); ) {
                Shell* shell = *it;
                int looser = shell->moveShell();
                if (looser == 1 || looser == 2) {
                    break;
                }

                if (shell->shouldBeDestroyed) {
                    shell->destroyMyself();
                } 
                else {
                    ++it;
                }
            }

            if (tank1.getRemainingShells() == 0 && tank2.getRemainingShells()){step--;}
            ///need to be fixed 
            action1 = algo1();
            do action1
            result = algo2();
            do action2
        }
    }

    int getSteps() const {
        return steps;
    }

    int getWinner() const {
        return winner;
    }

    void setWinner(int w) {
        winner = w;
    }





    
};
