#include "cell.h"



Cell::Cell(int x, int y, char pattern = ' ') : id{0}, x{x}, y{y}, pattern{pattern} {}

char Cell::getPattern() const {
    return pattern;
}


void Cell::setPattern(char var, int id) {
    pattern = var;
    this->id = id;
}

void Cell::setPos(int x, int y) {
    this->x = x;
    this->y = y;
}

int Cell::getId() {
    return id;
}









