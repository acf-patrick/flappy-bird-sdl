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

    textures_ = TextureManager::get();
}

Game::~Game()
{
    delete textures_;

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
    while (running) 
    {
        while (SDL_PollEvent(&event))
            manageEvents(event);

        update();

        SDL_RenderClear(renderer_);
        render();
        SDL_RenderPresent(renderer_);
    }
}

void Game::manageEvents(const SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_QUIT:
        running = false;
        break;

    default : ;
    }
}

void Game::update()
{
    objects_.update();
}

void Game::render()
{
    objects_.render();
}

GameObject* Game::getObject(const std::string& tag)
{
    return objects_.get(tag);
}