    #include "heavyboard.h"
    
    HeavyBoard::HeavyBoard(std::unique_ptr<AbstractBoard> &board): Decorator(std::move(board)) {}

    int HeavyBoard::getLength(int number){
        return board->getLength(number);
    }

    void HeavyBoard::createNext() {
        board->createNext();
    }

    char HeavyBoard::getCell(int row, int col) {
        return board->getCell(row, col);
    }


    void HeavyBoard::deleteRow(int y){
        board->deleteRow(y);
    }

    bool HeavyBoard::moveBlock(char dir, int repeat){
    if (dir == 'd') {
        for (int i = 0; i < repeat; ++i) {
            board->curBlock->down();
        }
    } else if (dir == 'r') {
        for (int i = 0; i < repeat; ++i) {
            board->curBlock->horizontal(1);      
        }
    } else if (dir == 'l') {
        for (int i = 0; i < repeat; ++i) {
            board->curBlock->horizontal(-1);
        }
    }
    if (board->isHeavy()) {
        board->curBlock->down();
    }
    if (dir == 'd') {
        return true;
    }
    if (!board->curBlock->down()) {
        board->drop();
        return false;
    }
    if (!board->curBlock->down()) {
        board->drop();
        return false;
    }
    return true;
    }

    bool HeavyBoard::searchID(int id){
        return board->searchID(id);
    }

    bool HeavyBoard::dropCenter() {
        return board->dropCenter();
    }

    int HeavyBoard::drop(){
        return board->drop();
    }

    void HeavyBoard::rotateBlock(std::string dir, int repeat){
        board->rotateBlock(dir, repeat);
    }

    int HeavyBoard::getScore(){
        return board->getScore();
    }

    int HeavyBoard::getLev(){
        return board->getLev();
    }

    void HeavyBoard::levelUp(){
        board->levelUp();
    }

    void HeavyBoard::levelDown(){
        board->levelDown();
    }

    int HeavyBoard::getPlayer() {
        return board->getPlayer();
    }
    
    char HeavyBoard::getNext(int row, int col){
        return board->getNext(row, col);
    }

    void HeavyBoard::changeNext(char type) {
        return board->changeNext(type);
    }

    char HeavyBoard::whatBoard() {
        return 'h';
    }


std::unique_ptr<AbstractBoard> HeavyBoard::releaseInnerComponent() {
    return std::move(board);
}


bool HeavyBoard::isHeavy() {
    return board->isHeavy();
}



void HeavyBoard::deleteCur() {
    board->deleteCur();
}

void HeavyBoard::random() {
    board->random();
}

void HeavyBoard::noRandom(std::string file) {
    board->noRandom(file);
}

void HeavyBoard::changeCur(char pattern) {
    board->changeCur(pattern);
}
