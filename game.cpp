#include "bird.h"
#include "game.h"
#include "base.h"
#include "pipe.h"
#include "texture.h"
#include "background.h"

#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>

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
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);

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

    std::ofstream file ("./score", std::ios::binary);
    file << maxScore_;

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

    while (running_) 
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
        running_ = false;
        break;
    case SDL_MOUSEBUTTONUP:
        if (state_ == PLAYING)
        {
            if (!dead_)
                bird_->step();
        }
        else if (state_ == GAMEOVER)
        {
            state_ = BEGIN;
            bird_->reset();
        }
        else if (state_ == BEGIN)
        {
            state_ = PLAYING;
            dead_ = false;
            resetPipes();
            bird_->toggleState();
        }
        break;
    default : ;
    }
}

void Game::update()
{
    if (state_ == BEGIN)
    {
        bird_->update();
        base_->update();
    }
    else if (state_ == PLAYING)
    {
        if (dead_)
        {
            if (!hasHitGround())
                bird_->update();
            else
                state_ = GAMEOVER;
            return;
        }

        for (auto object : objects_)
            object->update();

        for (auto pipe : pipes_)
            pipe->update();

        if (!pipes_.empty())
        {
            auto head = pipes_.front();
            auto pipePos = head->getRight();
            auto birdRect = bird_->getRect();
            if (pipePos < birdRect.x + birdRect.w && lastPipeHead_ != head)
            {
                lastPipeHead_ = head;
                score();
            }

            const int baseHeight = 112;
            if (head->collide(birdRect) || hasHitGround())
                dead();
        }
        
        createPipes();
    }
}

void Game::resetPipes()
{
    if (pipes_.empty())
        return;

    for (auto pipe : pipes_)
        delete pipe;
    pipes_.clear();
}

bool Game::hasHitGround()
{
    const int baseHeight = 112;
    auto bird = bird_->getRect();
    return bird.y + bird.h >= height_ - baseHeight;
}

void Game::dead()
{
    dead_ = true;
    if (score_ > maxScore_)
        maxScore_ = score_;
}

void Game::score()
{
    score_++;
}

void Game::render()
{
    // order matters

    background_->render();

    if (state_ != BEGIN)
        for (auto pipe : pipes_)
            pipe->render();
    
    bird_->render();
    base_->render();

    auto renderTexture = [&](const std::string& t) {
        SDL_Point tSize;
        auto texture = textures_->retrieve(t);
        SDL_QueryTexture(texture, NULL, NULL, &tSize.x, &tSize.y);

        SDL_Rect dest = {
            (width_ - tSize.x) / 2, (height_ - tSize.y) / 2,
            tSize.x, tSize.y
        };
        SDL_RenderCopy(renderer_, texture, NULL, &dest);
    };

    if (state_ != PLAYING)
    {
        darkenScreen();

        if (state_ == BEGIN)
            renderTexture("message");
        else if (state_ == GAMEOVER)
            renderTexture("gameover");
    }
}

void Game::darkenScreen()
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 100);
    SDL_RenderFillRect(renderer_, NULL);
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

void Game::loadScore()
{
    std::ifstream file("./score", std::ios::binary);
    if (file)
        file >> maxScore_;
    else
        std::cerr << "Failed to load score!" << std::endl;
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

