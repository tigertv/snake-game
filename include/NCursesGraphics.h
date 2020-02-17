#ifndef NCURSES_GRAPHICS_H_
#define NCURSES_GRAPHICS_H_

#include "AbstractGraphics.h"

class NCursesGraphics : public AbstractGraphics {

public:
    NCursesGraphics();
    void init() override;
    void exit() override;
    void render() override;
    void processInput() override;
};

#endif