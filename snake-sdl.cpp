#include <iostream>
#include "Game.h"
#include "SdlGraphics.h"

int main() {
    Game game;
    AbstractGraphics* graphics = new SdlGraphics();
    game.setGraphics(graphics);
    game.run();
    int score = game.getScore();
    std::cout << "Score: " << score << std::endl;
    delete graphics;
    return 0;
}
