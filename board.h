#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <string>
#include <memory>
#include <vector>
#include "cell.h"
#include "abstractboard.h"
#include "level.h"
#include "block.h"


class Board : public AbstractBoard {
    int playerID;
    std::unique_ptr<Block> nextblock;
    int score;
    int lev;
    std::unique_ptr<Level> level;
    std::string file;
    std::map<int, int> value;        //value records the level when a block is generated
    int seed;
    int fourDrops;
    int centerBlock;
    int heavy;
    int numBlock;
public:
    int getLength(int number) override;
    Board(int id, std::string file, int lev = 0, int seed = 1) ;
    void createNext() override;
    char getCell(int row, int col) override;
    void deleteRow(int y) override;
    bool moveBlock(char dir, int repeat) override;
    bool searchID(int id) override;
    bool dropCenter() override;
    int drop() override;
    void rotateBlock(std::string dir, int repeat) override;
    int getScore() override;
    int getLev() override;
    void levelUp() override;
    void levelDown() override;
    int getPlayer() override;
    char getNext(int row, int col) override;
    void changeNext(char type) override;
    char whatBoard() override;
    std::unique_ptr<AbstractBoard> releaseInnerComponent() override;
    bool isHeavy() override;
    void deleteCur() override;
    void random() override;
    void noRandom(std::string file) override;
    void changeCur(char pattern) override;
};

#endif

