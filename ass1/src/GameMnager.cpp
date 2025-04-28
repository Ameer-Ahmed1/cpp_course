#include <iostream>
#include <fstream>
#include <string>

class GameManager {
private:
    int steps = 40;
    int winner = -1;

public:
    GameManager() = default;
    
    void initalization(const std::string& filePath) {
        //BoardObject::setBoardSize(20, 20); // for example
        //matrix[x][y] = Empty::getInstance();  // ✅ Shared singleton instance//
        //to do
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filePath << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            // Process each line (you can implement your logic here)
            std::cout << "Read line: " << line << std::endl;
        }

        file.close();
        std::cout << "Game started with " << steps << " steps." << std::endl;


    }

    void start(){
        while (win != -1 and steps>0){
            move shell and check it has to be delted .
            for (Shell* shell : shells) {
                if (shell->shouldBeDestroyed) {
                tank.removeShell(shell);
                }
            }
            update steps
            call the alfgo
            do the action
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
