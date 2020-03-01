#ifndef SDL_GRAPHICS_H_
#define SDL_GRAPHICS_H_

#include <SDL2/SDL.h> 
#include "AbstractGraphics.h"

class SdlGraphics : public AbstractGraphics {
private:
    SDL_Window *window = nullptr;
    SDL_Renderer *wrenderer = nullptr;
    SDL_Rect destR;
    SDL_Rect srcR;
    SDL_Texture* sprite;

public:
    SdlGraphics();
    void init() override;
    void exit() override;
    void render() override;
    void processInput() override;
};

#endif