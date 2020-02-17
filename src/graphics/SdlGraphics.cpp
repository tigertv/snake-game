#include "SdlGraphics.h"
#include <SDL2/SDL.h> 


SdlGraphics::SdlGraphics() {

}

void SdlGraphics::init() {
    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 768;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to init SDL: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return;
    }

    wrenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // init keys
    keys[SDLK_RIGHT] = Key::RIGHT;
    keys[SDLK_LEFT] = Key::LEFT;
    keys[SDLK_UP] = Key::UP;
    keys[SDLK_DOWN] = Key::DOWN;
    keys[SDLK_1] = Key::KEY_1;
    keys[SDLK_ESCAPE] = Key::ESC;
}

void SdlGraphics::exit() {
    SDL_DestroyRenderer(wrenderer);
    wrenderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

void SdlGraphics::render() {

    SDL_SetRenderDrawColor( wrenderer, 0, 0, 0, 255);
    SDL_RenderClear(wrenderer);

    Snake* snake = game->getSnake();
    BorderFrame* borderFrame = game->getBorderFrame();
    Food* food = game->getFood();

    // render snake
    std::list<std::pair<int, int>> *coords = snake->getCoordinates();
    std::list<std::pair<int, int>>::iterator it = coords->begin();
    
    const int cellSize = 14;
    
    // render head
    SDL_SetRenderDrawColor(wrenderer, 0, 255, 0, 0);
    SDL_Rect rect;
    rect.x = it->first * (cellSize + 1);
    rect.y = it->second * (cellSize + 1);
    rect.w = cellSize;
    rect.h = cellSize;
    SDL_RenderFillRect(wrenderer, &rect);

    // render body
    SDL_SetRenderDrawColor(wrenderer, 0, 235, 60, 255);
    for(it++; it != coords->end(); it++) {
        rect.x = it->first * (cellSize + 1);
        rect.y = it->second * (cellSize + 1);
        SDL_RenderFillRect(wrenderer, &rect);
    }

    // render boarders
    SDL_SetRenderDrawColor(wrenderer, 15, 56, 66, 255);
    for(int x = borderFrame->x; x <= borderFrame->x + borderFrame->width; x++) {
        rect.x = x * (cellSize + 1);
        rect.y = borderFrame->y * (cellSize + 1);
        SDL_RenderFillRect(wrenderer, &rect);
        rect.x = x * (cellSize + 1);
        rect.y = (borderFrame->y + borderFrame->height) * (cellSize + 1);
        SDL_RenderFillRect(wrenderer, &rect);
    }
    for(int y = borderFrame->y; y <= borderFrame->y + borderFrame->height; y++) {
        rect.x = borderFrame->x * (cellSize + 1);
        rect.y = y * (cellSize + 1);
        SDL_RenderFillRect(wrenderer, &rect);
        rect.x = (borderFrame->x + borderFrame->width) * (cellSize + 1);
        rect.y = y * (cellSize + 1);
        SDL_RenderFillRect(wrenderer, &rect);
    }
    
    // render food
    SDL_SetRenderDrawColor(wrenderer, 255, 0, 0, 255);
    rect.x = food->x * (cellSize + 1);
    rect.y = food->y * (cellSize + 1);
    SDL_RenderFillRect(wrenderer, &rect);
    
    SDL_RenderPresent(wrenderer);
}

void SdlGraphics::processInput() {

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            game->over();
            return;
        }

        if (e.type == SDL_KEYDOWN) {
            SDL_Keycode key = e.key.keysym.sym;
            if(this->keys.count(key)) {
                game->keyPressed(keys[key]);
            }
        }
    }

}
