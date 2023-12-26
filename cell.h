#ifndef CELL_H
#define CELL_H


class Cell {
    int id;
    int x;
    int y;
    char pattern;
public:
    Cell(int x, int y, char pattern);
    void setPattern(char var, int id);
    int getId();
    char getPattern() const;
    void setPos(int x, int y);
};

#endif
