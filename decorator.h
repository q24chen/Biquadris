#ifndef DECORATOR_H
#define DECORATOR_H


#include <memory>
#include "abstractboard.h"


class Decorator : public AbstractBoard {
    protected:
    std::unique_ptr<AbstractBoard> board;
    public: 
    Decorator(std::unique_ptr<AbstractBoard> board);
};


#endif
