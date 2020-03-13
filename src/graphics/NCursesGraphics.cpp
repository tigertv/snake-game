#include "NCursesGraphics.h"
#include <ncurses.h>

#define SNAKE_HEAD_PAIR 1
#define SNAKE_BODY_PAIR 2
#define WALL_PAIR 3
#define FOOD_PAIR 4

NCursesGraphics::NCursesGraphics() {

}

void NCursesGraphics::init() {
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

    // init keys
    keys[KEY_RIGHT] = Key::RIGHT;
    keys[KEY_LEFT] = Key::LEFT;
    keys[KEY_UP] = Key::UP;
    keys[KEY_DOWN] = Key::DOWN;
    keys['1'] = Key::KEY_1;
    keys[27] = Key::ESC;
}

void NCursesGraphics::exit() {
    erase();
    refresh();
    endwin();
}

void NCursesGraphics::render() {
    // clear screen
    clear();
    Snake* snake = game->getSnake();
    BorderFrame* borderFrame = game->getBorderFrame();
    Food* food = game->getFood();

    // render snake
    std::deque<SnakeBodyPart> *parts = snake->getBodyParts();
    SnakeBodyPart* part = &(*parts)[0];
    
    // render head
    attron(COLOR_PAIR(SNAKE_HEAD_PAIR));
    mvaddch(part->point.y, part->point.x, '@');
    attroff(COLOR_PAIR(SNAKE_HEAD_PAIR));

    // render body
    attron(COLOR_PAIR(SNAKE_BODY_PAIR));
    int size = parts->size();
    for (int i = 1; i < size; i++) {
        part = &(*parts)[i];

        char c;
        if (part->direction.x == 1 && part->direction.y == 0) {
            c = '>';
        } else if (part->direction.x == -1  && part->direction.y == 0) {
            c = '<';
        } else if (part->direction.y == 1 && part->direction.x == 0) {
            c = 'v';
        } else if (part->direction.y == -1 && part->direction.x == 0) {
            c = '^';
        } else if (part->direction.x == part->direction.y) {
            c = '/';
        } else {
            c = '\\';
        }
        mvaddch(part->point.y, part->point.x, c);
    }
    attroff(COLOR_PAIR(SNAKE_BODY_PAIR));

    // render boarders
    attron(COLOR_PAIR(WALL_PAIR));
    for(int x = borderFrame->x; x <= borderFrame->x + borderFrame->width; x++) {
        mvaddch(borderFrame->y, x, 'x');
        mvaddch(borderFrame->y + borderFrame->height, x, 'x');
    }
    for(int y = borderFrame->y; y <= borderFrame->y + borderFrame->height; y++) {
        mvaddch(y, borderFrame->x, 'x');
        mvaddch(y, borderFrame->x + borderFrame->width, 'x');
    }
    attroff(COLOR_PAIR(WALL_PAIR));

    // render food
    attron(COLOR_PAIR(FOOD_PAIR));
    mvaddch(food->y, food->x, 'F');
    attroff(COLOR_PAIR(FOOD_PAIR));
}

void NCursesGraphics::processInput() {
    int c = getch();

    if(this->keys.count(c)) {
        game->keyPressed(keys[c]);
    }
}