#include "level.h"
#include <string>
#include <iostream>


Level::Level(std::string file, int lev, int seed, bool norandom): file{file}, lev{lev}, seed{seed}, norandom{norandom}, currFile{file} {}

char Level::nextType(int lev) {
    if (norandom == true) {
        return nextType0();
    }
    if (lev == 0) {
        return nextType0();
    }
    else if (lev == 1) {
        return nextType1();
    }
    else if (lev == 2) {
        return nextType2();
    }
    else if (lev == 3) {
        return nextType3();
    }
    else {
        return nextType4();
    }
}

// ISJ
char Level::nextType0() {
    char type;
    if (currFile.length() == 0) {
        currFile = file;
    }
    type = currFile[0];
    currFile = currFile.substr(1);
    return type;
}

char Level::nextType1() {
    int n = rand() % 12;
    char c;
        if (n == 0 || n == 1) {
            c = 'S';
        }
        else if (n == 2 || n == 3) {
            c = 'Z';
        }
        else if (n == 4) {
            c = 'I';
        }
        else if (n == 5) {
            c = 'J';
        }
        else if (n == 6) {
            c = 'L';
        }
        else if (n == 7) {
            c = 'O';
        }
        else if (n == 8) {
            c = 'T';
        }
        return c;
}

char Level::nextType2() {
    int n = rand() % 7;
    char c;
        if (n == 0) {
            c = 'S';
        }
        else if (n == 1) {
            c = 'Z';
        }
        else if (n == 2) {
            c = 'I';
        }
        else if (n == 3) {
            c = 'J';
        }
        else if (n == 4) {
            c = 'L';
        }
        else if (n == 5) {
            c = 'O';
        }
        else if (n == 6) {
            c = 'T';
        }
        return c;
}

char Level::nextType3() {
    int n = rand() % 9;
    char c;
        if (n == 0 || n == 1) {
            c = 'S';
        }
        else if (n == 2 || n == 3) {
            c = 'Z';
        }
        else if (n == 4) {
            c = 'I';
        }
        else if (n == 5) {
            c = 'J';
        }
        else if (n == 6) {
            c = 'L';
        }
        else if (n == 7) {
            c = 'O';
        }
        else if (n == 8) {
            c = 'T';
        }
        return c;
}

char Level::nextType4() {
    int n = rand() % 9;
    char c;
        if (n == 0 || n == 1) {
            c = 'S';
        }
        else if (n == 2 || n == 3) {
            c = 'Z';
        }
        else if (n == 4) {
            c = 'I';
        }
        else if (n == 5) {
            c = 'J';
        }
        else if (n == 6) {
            c = 'L';
        }
        else if (n == 7) {
            c = 'O';
        }
        else if (n == 8) {
            c = 'T';
        }
        return c;
}


int Level::getDir() {
    return rand() % 4;
}

void Level::random() {
    norandom = false;
}
