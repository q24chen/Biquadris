#include "view.h"
#include <iomanip>

View::View(bool isGraphic): isGraphic{isGraphic}, graph{nullptr} {
    if (isGraphic) {
        graph = std::make_unique<Xwindow>(30*20, 30*20);
        graph->fillRectangle(0, 0, 30*20, 30*20, 0);
        //draw the board boundary
        graph->fillRectangle(18, 58, 11*20+4, 2, 1);
        graph->fillRectangle(360-2, 58, 11*20+4, 2, 1);

        graph->fillRectangle(18, 60, 2, 18*20, 1);
        graph->fillRectangle(12*20, 60, 2, 18*20, 1);
        graph->fillRectangle(18*20-2, 60, 2, 18*20, 1);
        graph->fillRectangle(29*20, 60, 2, 18*20, 1);
        
        graph->fillRectangle(18, 21*20, 11*20+4, 2, 1);
        graph->fillRectangle(360-2, 21*20, 11*20+4, 2, 1);
        graph->drawString(20, 22*20, "Next:");
        graph->drawString(18*20, 22*20, "Next:");
    }
}

void View::drawLevel(int level) {
    std::cout << "Level:" << std::string(4,' ') << level;
}   

void View::drawScore(int score) {
    std::cout << "Score:";
    std::cout << std::setw(5) << std::setfill(' ') << score;
}

void View::drawBoard(const std::unique_ptr<AbstractBoard> &p1, const std::unique_ptr<AbstractBoard> &p2) {
    for (int i = 0; i < 18; ++i) {
        for (int j = 0; j < 11; ++j) {
            std::cout << p1->getCell(i, j);
        }
        std::cout << std::string(6,' ');
        for (int j = 0; j < 11; ++j) {
            std::cout << p2->getCell(i, j);
        }
        std::cout << std::endl;
    }
}

void View::drawNext(const std::unique_ptr<AbstractBoard> &p) {
    std::cout << "Next:" << std::string(11,' ') << "Next:" << std::endl;
    int start;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (p->getNext(i,j) != ' ') {
                start = i;
                i = 4;
                break;
            }
        }
    }
    for (int i = start; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (p->getPlayer() == 1) {
                std::cout << p->getNext(i, j);
            } else {
                std::cout << ' ';
            }  
        }
        std::cout << std::string(13,' ');
        for (int j = 0; j < 4; ++j) {
            if (p->getPlayer() == 2) {
                std::cout << p->getNext(i, j);
            } else {
                std::cout << ' ';
            }  
        }
        std::cout << std::endl;
    }
}

void View::graphicDisplay(const std::unique_ptr<AbstractBoard> &p1, const std::unique_ptr<AbstractBoard> &p2, bool turn1) {
    if (!isGraphic) {
        return;
    }
    graph->fillRectangle(0, 0, 30 * 20, 2 * 20, 0);
    graph->drawString(20, 20, "Level:");
    graph->drawString(120, 20, std::to_string(p1->getLev()));
    graph->drawString(22*20, 20, "Level:");
    graph->drawString(22*20+100, 20, std::to_string(p2->getLev()));
    graph->drawString(20, 40, "Score:");
    graph->drawString(120, 40, std::to_string(p1->getScore()));
    graph->drawString(22*20, 40, "Score");
    graph->drawString(22*20+100, 40, std::to_string(p2->getScore()));
    
    for (int i = 0; i < 18; ++i) {
        for (int j = 0; j < 11; ++j) {
            graph->fillRectangle(20+j*20, 60 + i*20, 20, 20, graphicColor(p1->getCell(i, j)));
        }
        for (int j = 0; j < 11; ++j) {
            graph->fillRectangle(360 + j*20, 60 + i*20, 20, 20, graphicColor(p2->getCell(i, j)));
        }
    }
    graph->fillRectangle(0, 27*20, 30*20, 60, 0);
    if (turn1) {
        graph->fillRectangle(360, 23*20, 80, 80, 0);
        
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j){
                graph->fillRectangle(20+j*20, 23*20+i*20, 20, 20, graphicColor(p1->getNext(i, j)));
            }
        }
        graph->drawString(180, 28*20, "It is player 1's turn, please enter command!");
    } else {
        graph->fillRectangle(20, 23*20, 80, 80, 0);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j){
                graph->fillRectangle(360+j*20, 23*20+i*20, 20, 20, graphicColor(p2->getNext(i, j)));
            }
        }
        graph->drawString(180, 28*20, "It is player 2's turn, please enter command!");
    }  
}

int View::graphicColor(char type) {
    if (type == ' ') {
        return 0;
    } else if (type == 'I') {
        return 2;
    } else if (type == 'T') {
        return 3;
    } else if (type == 'S') {
        return 4;
    } else if (type == 'Z') {
        return 5;
    } else if (type == 'L') {
        return 6;
    } else if (type == 'J') {
        return 7;
    } else if (type == 'O') {
        return 8;
    } else if (type == '*') {
        return 1;
    } else {
        return 9;
    }
}

void View::graphicMsg(int x, int y, std::string msg) {
    if (isGraphic) {
        graph->drawString(x, y, msg);
    }
}

void View::graphicFill(int x, int y, int width, int height, int color) {
    if (isGraphic) {
        graph->fillRectangle(x, y, width, height, color);
    }
}
