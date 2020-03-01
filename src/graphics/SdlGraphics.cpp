#include "SdlGraphics.h"
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <iostream>

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

    // load sample.png into image
    SDL_Surface *image = IMG_Load("images/snake-tiles.png");
    sprite = SDL_CreateTextureFromSurface(wrenderer, image);
    SDL_FreeSurface(image);

    destR.x = 100;
    destR.y = 100;
    destR.w = 70;
    destR.h = 70;
    
    srcR.w = 64;
    srcR.h = 64;

    // init keys
    keys[SDLK_RIGHT] = Key::RIGHT;
    keys[SDLK_LEFT] = Key::LEFT;
    keys[SDLK_UP] = Key::UP;
    keys[SDLK_DOWN] = Key::DOWN;
    keys[SDLK_1] = Key::KEY_1;
    keys[SDLK_ESCAPE] = Key::ESC;
}

void SdlGraphics::exit() {
    SDL_DestroyTexture(sprite);
    SDL_DestroyRenderer(wrenderer);
    wrenderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

void SdlGraphics::render() {
    constexpr int tileSize = 64;

    SDL_SetRenderDrawColor( wrenderer, 0, 0, 0, 255);
    SDL_RenderClear(wrenderer);

    Snake* snake = game->getSnake();
    BorderFrame* borderFrame = game->getBorderFrame();
    Food* food = game->getFood();

    // render snake
    std::deque<SnakeBodyPart> *parts = snake->getBodyParts();

    const int cellSize = 20;
    
    // render head
    SDL_Rect rect;
    rect.x = (*parts)[0].point.x * cellSize;
    rect.y = (*parts)[0].point.y * cellSize;
    rect.w = cellSize;
    rect.h = cellSize;
    destR = rect;

    SnakeBodyPart* part = &(*parts)[0];
    if (part->direction.x == 1) {
        srcR.x = 4;
        srcR.y = 0;
    } else if (part->direction.x == -1) {
        srcR.x = 3;
        srcR.y = 1;
    } else if (part->direction.y == 1) {
        srcR.x = 4;
        srcR.y = 1;
    } else {
        srcR.x = 3;
        srcR.y = 0;
    }

    srcR.x *= tileSize;
    srcR.y *= tileSize;
    SDL_RenderCopy(wrenderer, this->sprite, &srcR, &destR);

    // render body  
    int size = (*parts).size();
    int i = 1;
    for (; i < size - 1; i++) {
        part = &(*parts)[i];
        
        rect.x = part->point.x * cellSize;
        rect.y = part->point.y * cellSize;
        destR = rect;

        srcR.x = 1 + part->direction.x;
        srcR.y = 1 + part->direction.y;
        srcR.x *= tileSize;
        srcR.y *= tileSize;
        SDL_RenderCopy(wrenderer, this->sprite, &srcR, &destR);
    }

    // render tail
    if (i > 0) {
        part = &(*parts)[i];
        
        rect.x = part->point.x * cellSize;
        rect.y = part->point.y * cellSize;
        destR = rect;
        
        if (part->direction.x == 1) {
            srcR.x = 4;
            srcR.y = 2;
        } else if (part->direction.x == -1) {
            srcR.x = 3;
            srcR.y = 3;
        } else if (part->direction.y == 1) {
            srcR.x = 4;
            srcR.y = 3;
        } else {
            srcR.x = 3;
            srcR.y = 2;
        }

        srcR.x *= tileSize;
        srcR.y *= tileSize;
        SDL_RenderCopy(wrenderer, this->sprite, &srcR, &destR);
    }

    // render boarders
    SDL_SetRenderDrawColor(wrenderer, 15, 56, 66, 255);
    for(int x = borderFrame->x; x <= borderFrame->x + borderFrame->width; x++) {
        rect.x = x * (cellSize + 0);
        rect.y = borderFrame->y * (cellSize + 0);
        SDL_RenderFillRect(wrenderer, &rect);
        rect.x = x * (cellSize + 0);
        rect.y = (borderFrame->y + borderFrame->height) * (cellSize + 0);
        SDL_RenderFillRect(wrenderer, &rect);
    }
    for(int y = borderFrame->y; y <= borderFrame->y + borderFrame->height; y++) {
        rect.x = borderFrame->x * cellSize;
        rect.y = y * (cellSize + 0);
        SDL_RenderFillRect(wrenderer, &rect);
        rect.x = (borderFrame->x + borderFrame->width) * cellSize;
        rect.y = y * cellSize;
        SDL_RenderFillRect(wrenderer, &rect);
    }
    
    // render food
    rect.x = food->x * cellSize;
    rect.y = food->y * cellSize;
    destR = rect;
    srcR.x = 0;
    srcR.y = tileSize * 3;
    srcR.w = tileSize;
    srcR.h = tileSize;
    SDL_RenderCopy(wrenderer, this->sprite, &srcR, &destR);
    
    // give sdl to know when to render
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
