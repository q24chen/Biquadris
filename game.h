#ifndef GAME_H
#define GAME_H

#include <string>
#include <memory>
#include "abstractboard.h"
#include "view.h"


class Game {
    std::unique_ptr<AbstractBoard> board1;
    std::unique_ptr<AbstractBoard> board2;
    std::unique_ptr<View> display;
    int startlevel;
    bool isgraphic;
    int seed;
    int hScore;
    bool turn1 = true;
    std::string filename1;
    std::string filename2;
    std::string file1;
    std::string file2;

    public:
    Game(int startlevel, bool isgraphic, int seed, std::string filename1 = "sequence1.txt", std::string filename2 = "sequence2.txt");
    std::string readFile(std::string filename);
    bool cmdInterpreter(std::unique_ptr<AbstractBoard> &cur, std::istream &in, std::unique_ptr<AbstractBoard> &op);
    void render(const std::unique_ptr<AbstractBoard> &p1, const std::unique_ptr<AbstractBoard> &p2);
    void startGame();
    void restart();
};



#endif
