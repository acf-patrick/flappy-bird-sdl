#include "game.h"
#include <iostream>

Game* Game::instance = nullptr;

Game* Game::get() 
{
    if (!instance)
        instance = new Game;
    return instance;
}

Game::Game()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        log("Failed to initialize subsystems.");

    if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &window_, &renderer_) < 0)
        log("Failed to create window!");

    SDL_SetWindowTitle(window_, "Flappy Bird");
}

Game::~Game()
{
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);

    instance = nullptr;
}

SDL_Renderer* Game::getRenderer()
{
    return renderer_;
}

void Game::log(const std::string& message)
{
    std::cerr << message << std::endl;
    std::cerr << SDL_GetError() << std::endl;
    exit(1);
}

void Game::run()
{
    SDL_Event event;
    while (true) 
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            break;
        SDL_RenderClear(renderer_);
        SDL_RenderPresent(renderer_);
    }
}