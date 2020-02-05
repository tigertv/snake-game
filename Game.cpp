#include "Game.h"
#include <ncurses.h>
#include <unistd.h>

#define SNAKE_HEAD_PAIR 1
#define SNAKE_BODY_PAIR 2
#define WALL_PAIR 3
#define FOOD_PAIR 4

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

    erase();
    refresh();
    endwin();
}

void Game::init() {
    // init
    initscr();
    // TODO check for failing

    cbreak();    // Character input doesnt require the <enter> key anymore
    curs_set(0); // Makes the blinking cursor invisible
    noecho();    // Wont print the keys received through input
    nodelay(stdscr, TRUE); // Wont wait for input
    keypad(stdscr, TRUE);  // Support for extra keys (life F1, F2, ... )

    // Ncurses' global variable meaning number of milliseconds
    // to wait after the user presses ESC.
    //
    // VIM uses 25ms, so should you.
    // Source: http://en.chys.info/2009/09/esdelay-ncurses/
    ESCDELAY = 25;

    refresh();   // Refresh the layout

    start_color();
    init_pair(SNAKE_HEAD_PAIR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(WALL_PAIR, COLOR_CYAN, COLOR_MAGENTA);
    init_pair(SNAKE_BODY_PAIR, COLOR_GREEN, COLOR_BLACK);
    init_pair(FOOD_PAIR, COLOR_RED, COLOR_BLACK);
    
}

void Game::processInput() {
    int c = getch();

    switch (c) {
        case KEY_LEFT:
            snake.changeDirection(Direction::LEFT);
            break;

        case KEY_DOWN:
            snake.changeDirection(Direction::DOWN);
            break;

        case KEY_UP:
            snake.changeDirection(Direction::UP);
            break;

        case KEY_RIGHT:
            snake.changeDirection(Direction::RIGHT);
            break;

        case '1':
            snake.grow();
            break;

        case 27: // KEY_ESC
            // exit from loop
            this->isPlaying = false;
            break;
    }
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
        this->score += 10;
        food = foodBuilder.getFood();
    }
}

void Game::render() {
    // clear screen
    clear();
    
    // render snake
    std::list<std::pair<int, int>> *coords = snake.getCoordinates();
    std::list<std::pair<int, int>>::iterator it = coords->begin();
    
    // render head
    attron(COLOR_PAIR(SNAKE_HEAD_PAIR));
    mvaddch(it->second, it->first, '@');
    attroff(COLOR_PAIR(SNAKE_HEAD_PAIR));

    // render body
    attron(COLOR_PAIR(SNAKE_BODY_PAIR));
    for(it++; it != coords->end(); it++) {
        //mvprintw(it->second, it->first, "o");
        mvaddch(it->second, it->first, 'o');
    }
    attroff(COLOR_PAIR(SNAKE_BODY_PAIR));

    // render boarders
    attron(COLOR_PAIR(WALL_PAIR));
    for(int x = borderFrame.x; x <= borderFrame.x + borderFrame.width; x++) {
        mvaddch(borderFrame.y, x, 'x');
        mvaddch(borderFrame.y + borderFrame.height, x, 'x');
    }
    for(int y = borderFrame.y; y <= borderFrame.y + borderFrame.height; y++) {
        mvaddch(y, borderFrame.x, 'x');
        mvaddch(y, borderFrame.x + borderFrame.width, 'x');
    }
    attroff(COLOR_PAIR(WALL_PAIR));

    // render food
    attron(COLOR_PAIR(FOOD_PAIR));
    mvaddch(this->food->y, this->food->x, 'F');
    attroff(COLOR_PAIR(FOOD_PAIR));
}

int Game::getScore() {
    return this->score;
}
