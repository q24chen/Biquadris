    #include "blindboard.h"
    #include <iostream>
    
    BlindBoard::BlindBoard(std::unique_ptr<AbstractBoard> &board): Decorator(std::move(board)) {}

    int BlindBoard::getLength(int number){
        return board->getLength(number);
    }

    void BlindBoard::createNext() {
        board->createNext();
    }

    char BlindBoard::getCell(int row, int col) {
        if (3 <= row && row <= 12 && 3 <= col && col <= 9) {
            return '?';
        }
        return board->getCell(row, col);
    }


    void BlindBoard::deleteRow(int y){
        board->deleteRow(y);
    }

    bool BlindBoard::moveBlock(char dir, int repeat){
        return board->moveBlock(dir, repeat);
    }

    bool BlindBoard::searchID(int id){
        return board->searchID(id);
    }

    bool BlindBoard::dropCenter(){
        return board->dropCenter();
    }

    int BlindBoard::drop(){
        return board->drop();
    }

    void BlindBoard::rotateBlock(std::string dir, int repeat){
        board->rotateBlock(dir,repeat);
    }

    int BlindBoard::getScore(){
        return board->getScore();
    }

    int BlindBoard::getLev(){
        return board->getLev();
    }

    void BlindBoard::levelUp(){
        board->levelUp();
    }

    void BlindBoard::levelDown(){
        board->levelDown();
    }

    int BlindBoard::getPlayer() {
        return board->getPlayer();
    }
    
    char BlindBoard::getNext(int row, int col){
        return board->getNext(row, col);
    }

    void BlindBoard::changeNext(char type) {
        return board->changeNext(type);
    }

    char BlindBoard::whatBoard() {
        return 'b';
    }


std::unique_ptr<AbstractBoard> BlindBoard::releaseInnerComponent() {
    return std::move(board);
}

bool BlindBoard::isHeavy() {
    return board->isHeavy();
}


void BlindBoard::deleteCur() {
    board->deleteCur();
}

void BlindBoard::random() {
    board->random();
}

void BlindBoard::noRandom(std::string file) {
    board->noRandom(file);
}

void BlindBoard::changeCur(char pattern) {
    board->changeCur(pattern);
}
