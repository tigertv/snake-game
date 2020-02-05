#include <iostream>
#include "Game.h"
#include "NCursesWrapper.h"

int main() {
    Game game;
    IWrapper* wrapper = new NCursesWrapper();
    game.setWrapper(wrapper);
    game.run();
    int score = game.getScore();
    std::cout << "Score: " << score << std::endl;
    delete wrapper;
    return 0;
}
