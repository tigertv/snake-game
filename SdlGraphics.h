#ifndef SDL_GRAPHICS_H_
#define SDL_GRAPHICS_H_

#include <SDL2/SDL.h> 

class Game;
#include "IGraphics.h"
#include "Game.h"

class SdlGraphics : public IGraphics {
private:
    SDL_Window *window = nullptr;
    SDL_Renderer *wrenderer = nullptr;
    
public:
    SdlGraphics();
    void init() override;
    void exit() override;
    void render() override;
    void processInput() override;
};

#endif