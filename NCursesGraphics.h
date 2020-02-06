#ifndef NCURSES_GRAPHICS_H_
#define NCURSES_GRAPHICS_H_

class Game;
#include "IGraphics.h"
#include "Game.h"

class NCursesGraphics : public IGraphics {

public:
    NCursesGraphics();
    void init() override;
    void exit() override;
    void render() override;
    void processInput() override;
};

#endif