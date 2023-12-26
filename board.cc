#include <iostream>
#include <set>
#include <sstream>
#include "board.h"
using namespace std;

int Board::getLength(int number) {
    if (number == 0) {
        return 1; // zero has one digit
    }

    int length = 0;
    while (number != 0) {
        length++;
        number /= 10;
    }
    return length;
}

Board::Board(int playerID, std::string file, int lev, int seed): playerID{playerID}, score{0}, 
    lev{lev}, file{file}, seed{seed}, numBlock{1} {
    curBlock = nullptr;
    for (int i = 0; i < 18 ; i++) {
        grid.emplace_back(vector<unique_ptr<Cell>>());
        for (int j = 0; j < 11; j++) {
            grid[i].push_back(make_unique<Cell> (i, j, ' '));
        }
    }
    level = make_unique<Level>(file, lev, seed, false);
    nextblock = make_unique<Block>(level->nextType(lev), lev, grid, level->getDir(), numBlock);
    fourDrops = 0;
    centerBlock = -1;
    if (lev >= 3) {
        heavy = 1;
    } else {
        heavy = 0;
    }
}


void Board::createNext() {
    if (!nextblock->canFit()) {
        throw 0;
    }
    if (nextblock->getLev() == 4) {
        fourDrops ++;
    }
    curBlock = move(nextblock);
    ++numBlock;
    curBlock->update(curBlock->getPattern(), curBlock->geID());
    value[curBlock->geID()] = curBlock->getLev();         
    nextblock = make_unique<Block>(level->nextType(lev), lev, grid, level->getDir(), numBlock);
}

char Board::getCell(int row, int col) {
    return grid[row][col]->getPattern();
}


void Board::deleteRow(int x) {                      //havn't been tested
    grid.erase(grid.begin() + x);
    for (int i = x - 1 ; i >= 0; i--) {
        for (int j = 0; j < 11; j++) {
            grid[i][j]->setPos(i + 1, j);
        }
    }
    grid.insert(grid.begin(), vector<unique_ptr<Cell>>());
    for (int i = 0; i < 11; i++) {
        grid[0].emplace_back(make_unique<Cell>(0, i, ' '));
    }
}

bool Board::moveBlock(char dir, int repeat) {
    if (dir == 'd') {
        for (int i = 0; i < repeat; ++i) {
            curBlock->down();
        }
    } else if (dir == 'r') {
        for (int i = 0; i < repeat; ++i) {
            curBlock->horizontal(1);
        }
    } else if (dir == 'l') {
        for (int i = 0; i < repeat; ++i) {
            curBlock->horizontal(-1);
        }
    }
    for (int i = 0; i < heavy; i++) {
        curBlock->down();
    }
    return true;
}

bool Board::searchID(int id) {
    for (int i = 0; i < 18; i++ ) {
        for (int j = 0; j < 11; j++) {
            if(id == grid[i][j]->getId()) {
                return true;
            }
        }
    }
    return false;
}

bool Board::dropCenter() {
    if (grid[3][5]->getPattern() != ' ') {
        return false;
    }
    for (int i = 4; i < 18; i++) {
        if (grid[i][5]->getPattern() != ' ') {
            grid[i-1][5]->setPattern('*', centerBlock);
            value[centerBlock] = 4;
            centerBlock--;
            return true;
        }
    }
    grid[17][5]->setPattern('*', centerBlock);
    value[centerBlock] = 4;
    centerBlock--;
    return true;
}

int Board::drop() {                    // when a block drops, we need to delete filled rows and add socre.
    moveBlock('d', 15);
    int rowsDel = 0;                    // records the number of rows deleted
    for (int i = 17; i >= 3; i--) {
        bool gap = false;;
        for (int j = 0; j < 11; j++) {
            if (grid[i][j]->getPattern() == ' ') {
                gap = true;
                break;
            }
        }
        if (!gap) {  
                                        // if there are no gaps in a row(a row is filled)
            std::vector<int> collection;     //a collection of the ID of all the block on the filled row                 
            for (int k = 0; k < 11; k++) {
                collection.push_back(grid[i][k]->getId());
            }
            std::set<int> unique_numbers(collection.begin(), collection.end());
            std::vector<int> ids(unique_numbers.begin(), unique_numbers.end());  // delete repetitive ID in the vector
            deleteRow(i);
            i++;
            rowsDel++;
            for (auto k = ids.begin(); k != ids.end(); k++) {
                if (!searchID(*k)) {                                        // the block is completely removed
                    if (value[*k] == 4) {
                        fourDrops = 0;
                    }
                    int blockLevel = value[*k] + 1;
                    blockLevel *= blockLevel;
                    score += blockLevel;
                    value.erase(*k);
                }
            }
        }
    }
    if (rowsDel != 0) {
        score += (rowsDel + lev) * (rowsDel + lev);
    }
    if (lev == 4 && fourDrops % 5 == 0 && fourDrops != 0) {
        if (!dropCenter()) {
            throw -1;                         // you lose the game;
        }
    }
    return rowsDel;
}

void Board::rotateBlock(string dir, int repeat) {
    if (dir == "cw") {
        for (int i = 0; i < repeat; ++i) {
            curBlock->cw();
        }
    } else {
        for (int i = 0; i < repeat; ++i) {
            curBlock->ccw();
        }
    }
    for (int i = 0; i < heavy; i++) {
        curBlock->down();
    }
}


int Board::getScore() {
    return score;
};

int Board::getLev() {
    return lev;
}

void Board::levelUp() {
    if (lev < 4) {
        lev++;
    }
    if (lev >= 3) {
        heavy = 1;
    }
}

void Board::levelDown() {
    if (lev > 0) {
        lev--;
    }
    if (lev < 3) {
        heavy = 0;
    }
}

int Board::getPlayer() {
    return playerID;
}

char Board::getNext(int row, int col) {
    return nextblock->getCell(row, col);
}

void Board::changeNext(char type) {
    nextblock = make_unique<Block>(type, lev, grid, level->getDir(), numBlock);
}


char Board::whatBoard() {
    return 'n';
}

std::unique_ptr<AbstractBoard> Board::releaseInnerComponent() {
    return nullptr;
}

bool Board::isHeavy() {
    return heavy;
}

void Board::deleteCur() {
    if (curBlock->getLev() == 4) {
        fourDrops--;
    }
    curBlock->removeCur();
}

void Board::random() {
    if (lev > 2) {
        level->random();
    }
}

void Board::noRandom(std::string file) {
    if (lev > 2) {
        level = make_unique<Level>(file, lev, seed, true);
    }
}

void Board::changeCur(char pattern)  {
    if (lev == 4) {
        fourDrops++;
    }
    curBlock = make_unique<Block>(pattern, lev, grid, level->getDir(), numBlock - 1);
    if (!curBlock->canFit()) {
        throw 0;
    }
    curBlock->update(pattern, curBlock->geID());
    value[curBlock->geID()] = curBlock->getLev();
}
