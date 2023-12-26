#ifndef VIEW_H
#define VIEW_H
#include <memory>
#include "abstractboard.h"
#include "window.h"


class View {
    bool isGraphic;
    std::unique_ptr<Xwindow> graph;

public:
    View(bool isGraphic);
    void drawLevel(int level);
    void drawScore(int score);
    void drawBoard(const std::unique_ptr<AbstractBoard> &p1, const std::unique_ptr<AbstractBoard> &p2);
    void drawNext(const std::unique_ptr<AbstractBoard> &p);
    void graphicDisplay(const std::unique_ptr<AbstractBoard> &p1, const std::unique_ptr<AbstractBoard> &p2, bool turn1);
    int graphicColor(char type);
    void graphicMsg(int x, int y, std::string msg);
    void graphicFill(int x, int y, int width, int height, int color);
};

#endif
