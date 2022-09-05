#include "game.h"
#include "base.h"
#include "background.h"

#include <vector>
#include <iostream>

Game* Game::instance = nullptr;

Game* Game::get() 
{
    if (!instance)
        new Game;
    return instance;
}

Game::Game()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        log("Failed to initialize subsystems.");

    if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &window_, &renderer_) < 0)
        log("Failed to create window!");

    instance = this;

    SDL_SetWindowTitle(window_, "Flappy Bird");

    textures_ = TextureManager::get();

    loadAssets();
    createObjects();
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

        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0xff);
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

void Game::loadAssets()
{
    /* Loading sprites */

    std::vector<std::string> sprites = {
        "background-day", "background-night", "base",
        "bluebird-downflap", "bluebird-upflap", "bluebird-midflap",
        "redbird-downflap", "redbird-upflap", "redbird-midflap",
        "yellowbird-downflap", "yellowbird-upflap", "yellowbird-midflap",
        "pipe-green", "pipe-red", "message", "gameover"
    };
    for (int i = 0; i < 10; ++i)
        sprites.emplace_back(std::to_string(i));

    for (auto sprite : sprites)
        if (!textures_->load("./Assets/sprites/" + sprite + ".png", sprite))
            exit(1);

    /* Loading audios */
}

void Game::createObjects()
{
    objects_.push(new Background, "background");
    objects_.push(new Base, "base");
}

SDL_Point Game::getWindowSize()
{
    return { width, height };
}