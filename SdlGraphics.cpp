#include "SdlGraphics.h"
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>


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
    
    const int cellSize = 15;
    
    // render head
    SDL_SetRenderDrawColor(wrenderer, 0, 255, 0, 0);
    SDL_Rect rect;
    rect.x = it->first * cellSize;
    rect.y = it->second * cellSize;
    rect.w = cellSize;
    rect.h = cellSize;
    SDL_RenderFillRect(wrenderer, &rect);

    // render body
    SDL_SetRenderDrawColor(wrenderer, 0, 235, 60, 255);
    for(it++; it != coords->end(); it++) {
        rect.x = it->first * cellSize;
        rect.y = it->second * cellSize;
        SDL_RenderFillRect(wrenderer, &rect);
    }

    // render boarders
    SDL_SetRenderDrawColor(wrenderer, 15, 56, 66, 255);
    for(int x = borderFrame->x; x <= borderFrame->x + borderFrame->width; x++) {
        rect.x = x * cellSize;
        rect.y = borderFrame->y * cellSize;
        SDL_RenderFillRect(wrenderer, &rect);
        rect.x = x * cellSize;
        rect.y = (borderFrame->y + borderFrame->height) * cellSize;
        SDL_RenderFillRect(wrenderer, &rect);
    }
    for(int y = borderFrame->y; y <= borderFrame->y + borderFrame->height; y++) {
        rect.x = borderFrame->x * cellSize;
        rect.y = y * cellSize;
        SDL_RenderFillRect(wrenderer, &rect);
        rect.x = (borderFrame->x + borderFrame->width) * cellSize;
        rect.y = y * cellSize;
        SDL_RenderFillRect(wrenderer, &rect);
    }
    
    // render food
    SDL_SetRenderDrawColor(wrenderer, 255, 0, 0, 255);
    rect.x = food->x * cellSize;
    rect.y = food->y * cellSize;
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
            Snake* snake = game->getSnake();

            //SDL_BlitSurface(imgSurf, NULL, defaultSurface, NULL);
            //SDL_UpdateWindowSurface(window);

            switch( e.key.keysym.sym ) {
                case SDLK_LEFT: snake->changeDirection(Direction::LEFT); break;
                case SDLK_RIGHT: snake->changeDirection(Direction::RIGHT); break;
                case SDLK_UP: snake->changeDirection(Direction::UP); break;
                case SDLK_DOWN: snake->changeDirection(Direction::DOWN); break;
                case SDLK_1: snake->grow(); break;
                case SDLK_ESCAPE: game->over(); break;
                default: break;
            }
        }
    }
    /*
    Snake* snake = game->getSnake();
    int c = getch();

    switch (c) {
        case KEY_LEFT:
            snake->changeDirection(Direction::LEFT);
            break;

        case KEY_DOWN:
            snake->changeDirection(Direction::DOWN);
            break;

        case KEY_UP:
            snake->changeDirection(Direction::UP);
            break;

        case KEY_RIGHT:
            snake->changeDirection(Direction::RIGHT);
            break;

        case '1':
            snake->grow();
            break;

        case 27: // KEY_ESC
            game->over();
            break;
    }
    //*/
}