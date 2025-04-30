#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class GameManager {
private:
    int winner = -1;
    Tank& tank1 ;
    Tank& tank2 ;
    RunAwayAlgorithm runner;
    ChaseAlgorithm chaser;
    std::string outputfile;
    int steps = 40;


    //write to output file
    void appendToFile(const std::string& message) {
        std::ofstream file(outputfile, std::ios::app);  // open in append mode
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file: " << outputfile << std::endl;
            return;
        }
        file << message << std::endl;
        file.close();
    }

public:

    GameBoard* initialization(const std::string& filePath,const std::string outputfile) {
        this.outputfile = outputfile;
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file " << filePath << std::endl;
            return nullptr;
        }

        int width, height;
        file >> width >> height;
        file.ignore();

        GameBoard* board = new GameBoard(width, height);
        int foundTanks = 0;

        for (int y = 0; y < height; ++y) {
            std::string line;
            std::getline(file, line);
            for (int x = 0; x < width; ++x) {
                char c = (x < line.size()) ? line[x] : ' ';
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
                        Tank* t = new Tank(Point(x, y), Direction::L, 16, 1);
                        board->matrix[x][y] = t;
                        tank1 = t;
                        foundTanks++;
                        break;
                    }
                    case '2': {
                        Tank* t = new Tank(Point(x, y), Direction::R, 16, 2);
                        board->matrix[x][y] = t;
                        tank2 = t;
                        foundTanks++;
                        break;
                    }
                    default:
                        board->matrix[x][y] = &Empty::getInstance();
                        break;
                }
            }
        }

        if (foundTanks != 2) {
            std::cerr << "Error: Must have exactly 2 tanks!\n";
            delete board;
            return nullptr;
        }

        return board;
    }
    void start(GameBoard* board){//-2 both loose , -1 tie ,1,2 winner
        int res;
        while (getSteps()>0){ 
            //updateing the waiting time and shooting time
            tank1.decreaseShootingTime();
            tank2.decreaseShootingTime();
            tank1.decreaseWaitingTime();
            tank2.decreaseWaitingTime();
            if 
            //moving the shels
            for (auto it = board->activeShells.begin(); it != board->activeShells.end(); ) {
                Shell* shell = *it;
                int res = shell->moveShell();
                if (res != -1) {
                    if (winner == -1) {
                        winner = res;  // first valid result
                    } else if (winner != res) {
                        winner = -2;  // conflicting result
                        break;
                    }
                }
                ++it;
            }            
            if (winner != -1){return winner;}
            board->clearInactiveShells();
            if (!(tank1.hasShellsRemaining())&& !(tank2.hasShellsRemaining())){steps--;}
            ///need to be fixed           
            char runnerAction = runner.decideAction(tank1, tank2, *board);//responsible of tank1
            char chaserAction = chaser.decideAction(tank2, tank1,*board);//responsible of tank2
            if (tank1.timeToMoveF()) {runnerAction ='F';}//DONT TAKE DECSION ACORADING TO ALGO
            if (tank2.timeToMoveF()) {chaserAction ='F';}//DONT TAKE DECSION ACORADING TO ALGO

            int res1 = handleaction(runnerAction ,tank1);
            int res2 = handleaction(chaserAction ,tank2);

            if (res1==0){appendToFile("bad step!");}
            if (res2==0){appendToFile("bad step!");}

            if (res1 == res2 && (res1 == 1 || res1 == 2)) {
                winner = res1;  // same winner
            }
            else if (res1 == -2 || res2 == -2 || (res1 == 1 && res2 == 2) || (res1 == 2 && res2 == 1)) {
                winner = -2;  // both lose or conflicting winners
            }
            else if (res1 == -1 && (res2 == 1 || res2 == 2)) {
                winner = res2;  // chaser wins
            }
            else if (res2 == -1 && (res1 == 1 || res1 == 2)) {
                winner = res1;  // runner wins
            }
            
            return winner;
        }
        return -1;
    }


    int handleaction(char action ,Tank &tank){
        if (action == 'S'){
            if (!tank.shoot()){appendToFile("can't shoot!");}
            else{appendToFile("shoot");
                tank.setLastAction(false);}
            return -1;
            }
        else if (action == 'F'){
            if (tank.waitingBackward) {
                tank.waitingBackward = false;  // cancel backward
                return -1;
            }
            int res = tank.moveForward();
            if (res != 0){appendToFile("moveForward");tank.setLastAction(false);}
            return res;
        }
        else if (action == 'B'){
            if (tank.waitingBackward) {
                if (tank.getbackwardWaitTime() > 0){return -1;}// Still waiting, nothing happens
                else {// Now perform the backward move
                    tank.waitingBackward = false;
                    int res= tank.moveBackward();
                    if (res != 0){appendToFile("movebackward");tank.setLastAction(true);}
                    return res;
                }
            }
            // If no backward waiting yet, start new backward request
            if (tank.getLastAction()){//the last action was backword
                int res= tank.moveBackward();
                if (res != 0){appendToFile("movebackward");tank.setLastAction(true);}
                return res;
            }
            tank.waitingBackward = true;
            tank.setbackwardWaitTime(2);
            return -1; // Stay in place for now
        }

        //rotaion ..
        else if (action == 'R'){
            if (tank.rotate(....)){
                appendToFile("rotation");
                tank.setLastAction(false);} 
            return -1;
        }
        else{return -1;}


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
