#ifndef GAME_H_
#define GAME_H_

class IWrapper;

#include "IWrapper.h"
#include "Snake.h"
#include "FoodBuilder.h"
#include "BorderFrame.h"

class Game {
private:
    IWrapper* wrapper;
    Snake snake;
    int score = 0;
    FoodBuilder foodBuilder;
    Food* food = nullptr;
    BorderFrame borderFrame;
    const std::clock_t frame = 300000l;
    bool isPlaying = false;

    void init();
    void processInput();
    void update();
    void render();
    

public:
    Game();
    virtual ~Game();
    void run();
    int getScore();
    Snake* getSnake();
    Food* getFood();
    BorderFrame* getBorderFrame();
    void setWrapper(IWrapper* wrapper);
    void over();
};

#endif