#ifndef ABSTRACT_GRAPHICS_H_
#define ABSTRACT_GRAPHICS_H_

class Game;
enum class Key;

#include "Game.h"
#include <map>

class AbstractGraphics {
protected:
    Game* game = nullptr;
    std::map<int, Key> keys;
public:
    virtual ~AbstractGraphics() {};
    virtual void init() = 0;
    virtual void exit() = 0;
    virtual void render() = 0;
    virtual void processInput() = 0;
    void setGame(Game* game);
};

#endif