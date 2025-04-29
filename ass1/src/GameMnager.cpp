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
    GameBoard* initialization(const std::string& filePath, Tank*& tank1, Tank*& tank2) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file " << filePath << std::endl;
            return nullptr;
        }
    
        int width, height;
        file >> width >> height;
        file.ignore(); // Move to the next line after reading width and height
    
        GameBoard* board = new GameBoard(width, height);
    
        int foundTanks = 0;
    
        for (int y = 0; y < height; ++y) {
            std::string line;
            std::getline(file, line);
    
            for (int x = 0; x < width; ++x) {
                char c = (x < line.size()) ? line[x] : ' '; // If line is short, assume spaces
    
                switch (c) {
                    case ' ':
                        board->matrix[x][y] = &Empty::getInstance();
                        break;
                    case '#':
                        board->matrix[x][y] = new Wall(Point(x, y));
                        break;
                    case '@':
                        board->matrix[x][y] = new Mine(Point(x, y));
                        break;
                    case '1': {
                        if (foundTanks >= 2) {
                            std::cerr << "Error: More than 2 tanks on board!" << std::endl;
                            delete board;
                            return nullptr;
                        }
                        Tank* t = new Tank(Point(x, y), Direction::L, 16, 1);
                        board->matrix[x][y] = t;
                        tank1 = t;
                        foundTanks++;
                        break;
                    }
                    case '2': {
                        if (foundTanks >= 2) {
                            std::cerr << "Error: More than 2 tanks on board!" << std::endl;
                            delete board;
                            return nullptr;
                        }
                        Tank* t = new Tank(Point(x, y), Direction::R, 16, 2);
                        board->matrix[x][y] = t;
                        tank2 = t;
                        foundTanks++;
                        break;
                    }
                    default:
                        std::cerr << "Warning: Unknown symbol '" << c << "' at (" << x << "," << y << "), treated as Empty." << std::endl;
                        board->matrix[x][y] = &Empty::getInstance();
                        break;
                }
            }
        }
    
        if (foundTanks != 2) {
            std::cerr << "Error: Must have exactly 2 tanks! Found " << foundTanks << std::endl;
            delete board;
            return nullptr;
        }
    
        return board;
    }
    void start(){
        int steps = 40
        while (getSteps()>0){

             // --- 1. Move tank1 shells ---
            for (auto it = tank1->activeShells.begin(); it != tank1->activeShells.end(); ) {
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
            action2 = algo2();
            switch{

            }
            switch{
                
            }

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
