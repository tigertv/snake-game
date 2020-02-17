#include <iostream>
#include "Game.h"
#include "OpenGlGraphics.h"

int main() {
    Game game;
    AbstractGraphics* graphics = new OpenGlGraphics();
    game.setGraphics(graphics);
    game.run();
    int score = game.getScore();
    std::cout << "Score: " << score << std::endl;
    delete graphics;
    return 0;
}
