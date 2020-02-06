#include <iostream>
#include "Game.h"
#include "NCursesGraphics.h"
#include "SdlGraphics.h"

int main() {
    Game game;
    //IGraphics* graphics = new NCursesGraphics();
    IGraphics* graphics = new SdlGraphics();
    game.setGraphics(graphics);
    game.run();
    int score = game.getScore();
    std::cout << "Score: " << score << std::endl;
    delete graphics;
    return 0;
}
