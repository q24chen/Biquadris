#include <iostream>
#include <string>
#include <memory>
#include "game.h"
#include <sstream>
using namespace std;


int main(int argc, char* argv[]) {
    bool isGraphical = true;
    int seed;
    int level = 0;
    string file1 = "sequence1.txt";
    string file2 = "sequence2.txt";

    for (int i = 0; i < argc; ++i) {
        if (string(argv[i]) == "-text") {
            isGraphical = false;
        } else if (string(argv[i]) == "-seed") {
            try{
                seed = std::stoi(argv[++i]);
            } catch (...) {
                std::cout << "wrong seed number" << endl;
            }
        } else if (string(argv[i]) == "-scriptfile1") {
            file1 = argv[++i];
        } else if (string(argv[i]) == "-scriptfile2") {
            file2 = argv[++i];
        } else if (string(argv[i]) == "-startlevel") {
            try{
                level = std::stoi(argv[++i]);
            } catch (...) {
                std::cout << "wrong level number" << endl;
            }
        } 
    }
    unique_ptr<Game> game{new Game(level, isGraphical, seed, file1, file2)};
    game->startGame();
}
