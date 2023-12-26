#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <cstdlib>

class Level {
    const std::string file;
    int lev;
    int seed;
    bool norandom;
    std::string currFile;
    
public:
    Level(std::string file, int lev = 0, int seed = 1, bool norandom = false);
    char nextType(int lev);
    char nextType0();
    char nextType1();
    char nextType2();
    char nextType3();
    char nextType4();
    int getDir();
    void noRandom(std::string file);
    void random();
};

#endif
