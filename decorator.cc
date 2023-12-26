#include "decorator.h"
#include <memory.h>

Decorator::Decorator(std::unique_ptr<AbstractBoard> board) : board(std::move(board)){}
