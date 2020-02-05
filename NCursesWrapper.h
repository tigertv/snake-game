#ifndef NCURSES_WRAPPER_H_
#define NCURSES_WRAPPER_H_

class Game;
#include "IWrapper.h"
#include "Game.h"

class NCursesWrapper : public IWrapper {

public:
    NCursesWrapper();
    void init() override;
    void exit() override;
    void render() override;
    void processInput() override;
};

#endif