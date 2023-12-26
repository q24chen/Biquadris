#ifndef ABSTRACTBOARD_H
#define ABSTRACTBOARD_H
#include <memory>
#include <vector>
#include "cell.h"
#include "block.h"


class AbstractBoard {
protected:
    std::vector<std::vector<std::unique_ptr<Cell>>> grid;
public:
    std::unique_ptr<Block> curBlock;
    virtual int getLength(int number) = 0;
    virtual void createNext() = 0;
    virtual char getCell(int row, int col) = 0;
    virtual void deleteRow(int y) = 0;
    virtual bool moveBlock(char dir, int repeat) = 0;
    virtual bool searchID(int id) = 0;
    virtual bool dropCenter() = 0;
    virtual int drop() = 0;
    virtual void rotateBlock(std::string dir, int repeat) = 0;
    virtual int getScore() = 0;
    virtual int getLev() = 0;
    virtual void levelUp() = 0;
    virtual void levelDown() = 0;
    virtual int getPlayer() = 0;
    virtual char getNext(int row, int col) = 0;
    virtual void changeNext(char type) = 0;
    virtual char whatBoard() = 0;
    virtual std::unique_ptr<AbstractBoard> releaseInnerComponent() = 0;
    virtual bool isHeavy() = 0;
    virtual void deleteCur() = 0;
    virtual void random() = 0;
    virtual void noRandom(std::string file) = 0;
    virtual void changeCur(char pattern) = 0;
};

#endif
