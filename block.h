#ifndef BLOCK_H
#define BLOCK_H

#include <memory>
#include <string>
#include <vector>
#include <utility>
#include "cell.h"

class Block {
    std::vector<std::vector<std::unique_ptr<Cell>>> &board;
    char pattern;
    int lev;
    int blcol;
    int blrow;
    int rotate;
    std::vector<std::pair<int, int>> positions;
    int id = 0;
    bool heavy;

public:
    Block(char pattern, int lev, std::vector<std::vector<std::unique_ptr<Cell>>> &board, int rotate, int id);
    bool down();
    void horizontal(int dir);
    void cw();
    void ccw();
    void icw();
    void update(char word, int id);
    int geID();
    int getLev();
    char getPattern();
    char getCell(int row, int col);
    bool canFit();
    void removeCur();
};

#endif
