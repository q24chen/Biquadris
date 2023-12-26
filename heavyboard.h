#ifndef HEAVYBOARD_H
#define HEAVYBOARD_H

#include <memory>
#include "decorator.h"

class HeavyBoard: public Decorator {

    public :
    HeavyBoard(std::unique_ptr<AbstractBoard>& board);
    int getLength(int number) override;
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
