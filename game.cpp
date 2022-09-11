#include "bird.h"
#include "game.h"
#include "base.h"
#include "pipe.h"
#include "texture.h"
#include "background.h"

#include <vector>
#include <cstdlib>
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
    srand(time(0));

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        log("Failed to initialize subsystems.");

    if (SDL_CreateWindowAndRenderer(width_, height_, SDL_WINDOW_SHOWN, &window_, &renderer_) < 0)
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
    case SDL_MOUSEBUTTONUP:
        bird_->step();
        break;
    default : ;
    }
}

void Game::update()
{
    for (auto object : objects_)
        object->update();
    for (auto pipe : pipes_)
        pipe->update();
    createPipes();
}

void Game::render()
{
    background_->render();
    bird_->render();
    for (auto pipe : pipes_)
        pipe->render();
    base_->render();
}

void Game::createPipes()
{
    auto create = [&]() {
        auto pipe = new Pipe(background_->isDay() ? "green" : "red");
        pipes_.emplace_back(pipe);
    };

    if (pipes_.empty())
    {
        create();
        return;
    }

    // Create new pipe
    auto tail = pipes_.back();
    if (tail->getRight() < width_ - pipeSpace_)
        create();

    // Remove pipe
    auto head = pipes_.front();
    if (head->isOut())
    {
        pipes_.pop_front();
        delete head;
    }
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
    background_ = new Background;
    objects_.emplace_back(background_);
    
    bird_ = new Bird("red");
    objects_.emplace_back(bird_);
    
    base_ = new Base;
    objects_.emplace_back(base_);
}

SDL_Point Game::getWindowSize()
{
    return { width_, height_ };
}

