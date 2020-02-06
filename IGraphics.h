#ifndef IGRAPHICS_H_
#define IGRAPHICS_H_

class Game;
#include "Game.h"

class IGraphics {
protected:
    Game* game = nullptr;
public:
    virtual ~IGraphics() {};
    virtual void init() = 0;
    virtual void exit() = 0;
    virtual void render() = 0;
    virtual void processInput() = 0;
    void setGame(Game* game);
};

#endif