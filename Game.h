#ifndef GAME_H_
#define GAME_H_

class IGraphics;

#include "IGraphics.h"
#include "Snake.h"
#include "FoodBuilder.h"
#include "BorderFrame.h"

enum class Key {
    LEFT, RIGHT, UP, DOWN, ESC, KEY_1 
};

class Game {
private:
    IGraphics* graphics;
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
    void setGraphics(IGraphics* graphics);
    void over();
    void keyPressed(Key key);
};

#endif