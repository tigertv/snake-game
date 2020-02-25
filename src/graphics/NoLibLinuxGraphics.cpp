#include "NoLibLinuxGraphics.h"
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

NoLibLinuxGraphics::NoLibLinuxGraphics() {

}

void echoOff(void)
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);

    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void echoOn(void)
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);

    term.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

bool NoLibLinuxGraphics::kbhit() {
    struct termios original;
    tcgetattr(STDIN_FILENO, &original);

    struct termios term;
    memcpy(&term, &original, sizeof(term));

    term.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    int characters_buffered = 0;
    ioctl(STDIN_FILENO, FIONREAD, &characters_buffered);

    tcsetattr(STDIN_FILENO, TCSANOW, &original);
    return (characters_buffered != 0);
}

void NoLibLinuxGraphics::init() {
    // do not show pressed keys on the screen
    system("stty -echo");
    // hide cursor
    std::cout << "\e[?25l";
    
    // init keys
    keys['d'] = Key::RIGHT;
    keys['a'] = Key::LEFT;
    keys['w'] = Key::UP;
    keys['s'] = Key::DOWN;
    keys['1'] = Key::KEY_1;
    keys[27] = Key::ESC;
}

void NoLibLinuxGraphics::exit() {
    // show cursor
    std::cout << "\e[?25h";
    // show pressed keys on the screen
    system("stty echo");

    system("clear");
}

void NoLibLinuxGraphics::render() {
    Snake* snake = game->getSnake();
    BorderFrame* borderFrame = game->getBorderFrame();
    Food* food = game->getFood();

    std::system("clear");
    
    // render snake
    std::list<std::pair<int, int>> *coords = snake->getCoordinates();
    std::list<std::pair<int, int>>::iterator it = coords->begin();
    
    // render head
    std::cout << "\033[1;33m"; // change color
    renderChar(it->first, it->second, '@');

    // render body
    std::cout << "\033[1;32m"; // change color
    for(it++; it != coords->end(); it++) {
        renderChar(it->first, it->second, 'o');
    }

    // render boarders
    char ch = 'x';
    std::cout << "\033[30;45m"; // change color
    for(int x = borderFrame->x; x <= borderFrame->x + borderFrame->width; x++) {
        renderChar(x, borderFrame->y, ch);
        renderChar(x, borderFrame->y + borderFrame->height, ch);
    }
    for(int y = borderFrame->y; y <= borderFrame->y + borderFrame->height; y++) {
        renderChar(borderFrame->x, y, ch);
        renderChar(borderFrame->x + borderFrame->width, y, ch);
    }
    
    // render food
    std::cout << "\033[0;31m"; // change color
    renderChar(food->x, food->y, 'F');
}

void NoLibLinuxGraphics::processInput() {
    if (kbhit()) {
        int c = getchar();

        if(this->keys.count(c)) {
            game->keyPressed(keys[c]);
        }
    }
}

void NoLibLinuxGraphics::renderChar(int x, int y, char ch) {
    std::cout << "\033[" << y << ";" << x << "H";
    std::cout << ch << std::endl;
}