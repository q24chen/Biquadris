#include "block.h"
#include <vector>
#include <iostream>
#include "cell.h"



Block::Block(char pattern, int lev, std::vector<std::vector<std::unique_ptr<Cell>>> &board, int rotate, int id) :  
    board{board}, pattern{pattern}, lev{lev},  blcol{0}, blrow{3}, rotate{rotate}, id{id}{
    heavy = (lev >= 3);
    if (pattern == 'J') {
        positions.emplace_back(2, 0);
        positions.emplace_back(3, 0);
        positions.emplace_back(3, 1);
        positions.emplace_back(3, 2);
    } 
    else if (pattern == 'I') {
        positions.emplace_back(3, 0);
        positions.emplace_back(3, 1);
        positions.emplace_back(3, 2);
        positions.emplace_back(3, 3);
    } 
    else if (pattern == 'L') {
        positions.emplace_back(2, 2);
        positions.emplace_back(3, 0);
        positions.emplace_back(3, 1);
        positions.emplace_back(3, 2);
    } 
    else if (pattern == 'O') {
        positions.emplace_back(2, 0);
        positions.emplace_back(2, 1);
        positions.emplace_back(3, 0);
        positions.emplace_back(3, 1);
    } 
    else if (pattern == 'S') {
        positions.emplace_back(2, 2);
        positions.emplace_back(2, 1);
        positions.emplace_back(3, 0);
        positions.emplace_back(3, 1);
    } 
    else if (pattern == 'Z') {
        positions.emplace_back(2, 0);
        positions.emplace_back(2, 1);
        positions.emplace_back(3, 2);
        positions.emplace_back(3, 1);
    } 
    else if (pattern == 'T') {
        positions.emplace_back(2, 0);
        positions.emplace_back(2, 1);
        positions.emplace_back(2, 2);
        positions.emplace_back(3, 1);
    } 

    int dir = rotate;
    if (pattern == 'I') {
        if (dir % 2 == 1) {
            int cnt = 0;
            for (auto i = positions.begin(); i != positions.end(); i++) {
                i->first = blrow - cnt;
                i->second = blcol;
                cnt++;
            }
        }
    } else if (pattern == 'O') {
            return;
    } else {
        if (dir % 4 == 0) {
            return;
        }
        int brcol = blcol;
        int brrow = blrow;
        int count = 0;
        std::vector<std::pair<int, int>> temp;
        temp.assign(positions.begin(), positions.end());
        for (int i = 0; i < dir; ++i) {
            if (count % 2 == 0) {
                brcol = blcol + 2;
            } else {
                brcol = blcol + 1;
            }
            for (int i = 0; i < 4; ++i) {
                int x = temp[i].first;
                temp[i].first = blrow - brcol + temp[i].second;
                temp[i].second = blcol + brrow - x;
            }
            count++;
        }
        for (int i = 0; i < 4; ++i) {
            positions[i].first = temp[i].first;
            positions[i].second = temp[i].second;
        }
    }
}

void Block::update(char word, int id) {
    for (auto i = positions.begin(); i != positions.end(); i++) {
        board[i->first][i->second]->setPattern(word, id);
    }
}

bool Block::down() {
    bool canMove = true;
    for (auto i = positions.begin(); i != positions.end(); i++) {
        int row = i->first;
        int col = i->second;
        if ( (row + 1) >= 18 || !(board[row + 1][col]->getId() == 0 || 
                                  board[row + 1][col]->getId() == id)) { 
        canMove = false;
        }
    }
    if (canMove) {
        update(' ', 0);
        for (auto i = positions.begin(); i != positions.end(); i++) {
            i->first++;
        }
        ++blrow;
        update(pattern, id);
        return true;
    }
    return false;
}

void Block::horizontal(int dir) {
    bool canMove = true;
    for (auto i = positions.begin(); i != positions.end(); i++) {
        int row = i->first;
        int col = i->second;
        if ( ( (col + dir) >= 11 || (col + dir < 0) ) 
            || !(board[row][col + dir]->getId() == 0 
                || board[row][col + dir]->getId() == id)) { 
        canMove = false;
        }
    }
    if (canMove) {
        update(' ', 0);
        for (auto i = positions.begin(); i != positions.end(); i++) {
            i->second += dir;
        }
        blcol += dir;
        update(pattern, id);
    }
}

void Block::icw() {
    if (rotate %2 == 1 && blcol + 3 < 11) {
        update(' ', 0);
        int cnt = 0;
        for (auto i = positions.begin(); i != positions.end(); i++) {
            i->first = blrow;
            i->second = blcol + cnt;
            cnt++;
        }
        rotate = 0;
        update(pattern, id);
    } else if (rotate % 2 == 0) {
        update(' ', 0);
        int cnt = 0;
        for (auto i = positions.begin(); i != positions.end(); i++) {
            i->first = blrow - cnt;
            i->second = blcol;
            cnt++;
        }
        rotate = 1;
        update(pattern, id);
    }
}

void Block::cw() {
    if (pattern == 'I') {
        icw();
    } else if (pattern == 'O') {
        return;
    } else {
        int brcol = blcol;
        int brrow = blrow;
        int count = rotate;
        if (rotate % 2 == 0) {
            brcol = blcol + 2;
        } else {
            brcol = blcol + 1;
        }
        count++;
        for (int i = 0; i < 4; i++) { // check if can move
            int x = positions[i].first;
            int y = positions[i].second;
            if (blcol + brrow - x > 10) {
                // out of bounds error
                return;
            }
            if (board[blrow - brcol + y][blcol + brrow - x]->getId() != 0
                && board[blrow - brcol + y][blcol + brrow - x]->getId() != id) {
                // throw error
                return;
            }
        }
        
        // update current to blanks
        update(' ', 0);
        for (int i = 0; i < 4; i++) {
            int x = positions[i].first;
            int y = positions[i].second;
            positions[i].first = blrow - brcol + y;
            positions[i].second = blcol + brrow - x;
        }
        update(pattern, id);
        rotate++;
    }
}

void Block::ccw() {
    if (pattern == 'I') {
        icw();
    } else if (pattern == 'O') {
        return;
    }
    else {
        int tlcol = blcol;
        int tlrow = blrow;
        if (rotate % 2 == 0) {
            tlrow = blrow - 1;
        } else {
            tlrow = blrow - 2;
        }
        
        for (int i = 0; i < 4; i++) { // check if can move
            int x = positions[i].first;
            int y = positions[i].second;
            if ( blcol + x - tlrow > 10) {
                // out of bounds error
                return;
            } 
            if (board[blrow - y + tlcol][blcol + x - tlrow]->getId() != 0
                && board[blrow - y + tlcol][blcol + x - tlrow]->getId() != id) {
                //throw error
                return;
            }
        }
        // update current to blanks
        update(' ', 0);
        for (int i = 0; i < 4; i++) {
            int x = positions[i].first;
            int y = positions[i].second;
            positions[i].first = blrow - y + tlcol;
            positions[i].second = blcol + x - tlrow;
        }
        update(pattern, id);
        rotate++;
    }
}

int Block::geID(){
    return id;
}

int Block::getLev() {
    return lev;
}

char Block::getCell(int row, int col) {
    bool exist = false;
    for (int i = 0; i < 4; ++i) {
        if (positions[i].first == row && positions[i].second == col) {
            exist = true;
        }
    }
    if (exist) {
        return pattern;
    } else {
        return ' ';
    }
}

char Block::getPattern() {
    return pattern;
}

bool Block::canFit() {
    for (auto i = positions.begin(); i != positions.end(); i++) {
        if (board[i->first][i->second]->getPattern() != ' ') {
            return false;
        }
    }
    return true;
}


void Block::removeCur() {
    update(' ', 0);
}
