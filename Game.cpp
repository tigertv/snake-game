#include "Game.h"
#include <unistd.h>

Game::Game() : foodBuilder(&borderFrame), borderFrame(0, 0, 64, 32) {

}

Game::~Game() {

}

void Game::run() {
    this->init();
    this->food = foodBuilder.getFood();
    this->isPlaying = true;

    while(this->isPlaying) {
        // begin frame
        std::clock_t c_start = std::clock();
        
        this->processInput();
        this->update();
        this->render();

        // end frame
        std::clock_t c_end = std::clock();
        std::clock_t diff = this->frame - c_end + c_start;
        
        // delay
        usleep(diff);
    }

    graphics->exit();
}

void Game::setGraphics(IGraphics* graphics) {
    this->graphics = graphics;
    graphics->setGame(this);
}

void Game::init() {
    graphics->init();
}

void Game::processInput() {
    graphics->processInput();
}

void Game::update() {
    snake.update();

    // collisions?
    std::pair<int,int> head = snake.getHead();
    
    // itself collision
    std::list<std::pair<int, int>> *coords = snake.getCoordinates();
    std::list<std::pair<int, int>>::iterator it = coords->begin();
    for(it++; it != coords->end(); it++) {
        if (it->first == head.first && it->second == head.second) {
            // we have a collision
            this->isPlaying = false;
            // game over
            return;
        }
    }

    // border collision
    if (((head.first == borderFrame.x || head.first == borderFrame.x + borderFrame.width) && 
            head.second >= borderFrame.y && head.second < borderFrame.y + borderFrame.height) ||
        ((head.second == borderFrame.y || head.second == borderFrame.y + borderFrame.height) && 
            head.first >= borderFrame.x && head.first < borderFrame.x + borderFrame.width)
    ) {
        // you don't have to go out of the border space
        this->isPlaying = false;
        // game over
        return;
    }

    // has eaten food?
    if (head.first == food->x && head.second == food->y) {
        snake.grow();
        this->score += food->value;
        food = foodBuilder.getFood();
    }
}

void Game::render() {
    graphics->render();
}

int Game::getScore() {
    return this->score;
}

Snake* Game::getSnake() {
    return &snake;
}

Food* Game::getFood() {
    return food;
}

BorderFrame* Game::getBorderFrame() {
    return &borderFrame;
}

void Game::over(){
    isPlaying = false;
}