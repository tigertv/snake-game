#include "Game.h"
#include <unistd.h>

Game::Game() : foodBuilder(&borderFrame), borderFrame(0, 0, 32, 32) {

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

void Game::setGraphics(AbstractGraphics* graphics) {
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
    std::deque<SnakeBodyPart> *parts = snake.getBodyParts();
    SnakeBodyPart* head = &(*parts)[0];
    
    // itself collision
    int size = (int)parts->size();
    for(int i = 1; i < size; i++) {
        SnakeBodyPart& part = (*parts)[i];
        if(part.point.x == head->point.x && part.point.y == head->point.y) {
            // game over
            this->isPlaying = false;
            return;
        }
    }

    // border collision
    if(((head->point.x == borderFrame.x || head->point.x == borderFrame.x + borderFrame.width) && 
            head->point.y >= borderFrame.y && head->point.y < borderFrame.y + borderFrame.height) ||
        ((head->point.y == borderFrame.y || head->point.y == borderFrame.y + borderFrame.height) && 
            head->point.x >= borderFrame.x && head->point.x < borderFrame.x + borderFrame.width)
    ) {
        // you don't have to go out of the border space
        this->isPlaying = false;
        // game over
        return;
    }

    // has eaten food?
    if (head->point.x == food->x && head->point.y == food->y) {
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

void Game::keyPressed(Key key) {
    switch(key) {
        case Key::LEFT:
            snake.changeDirection(Direction::LEFT); 
            break;

        case Key::RIGHT:
            snake.changeDirection(Direction::RIGHT);
            break;

        case Key::UP:
            snake.changeDirection(Direction::UP);
            break;

        case Key::DOWN:
            snake.changeDirection(Direction::DOWN);
            break;

        case Key::KEY_1:
            snake.grow();
            break;

        case Key::ESC:
            this->over();
            break;
    }
}