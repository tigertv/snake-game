#include <iostream>
#include "Game.h"

int main() {
    Game game;
    game.run();
    int score = game.getScore();
    std::cout << "Score: " << score << std::endl;
    return 0;
}
