#ifndef IWRAPPER_H_
#define IWRAPPER_H_

class Game;
#include "Game.h"

class IWrapper {
protected:
    Game* game = nullptr;
public:
    virtual ~IWrapper() {};
    virtual void init() = 0;
    virtual void exit() = 0;
    virtual void render() = 0;
    virtual void processInput() = 0;
    void setGame(Game* game);
};

#endif