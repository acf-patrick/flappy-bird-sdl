#include "bird.h"
#include "texture.h"
#include <iostream>
Bird::Bird(const std::string& color)
{
    setColor(color);
    lastUpdateTick_ = SDL_GetTicks();
}

void Bird::update()
{
    auto curr = SDL_GetTicks();
    
    deltaTime_ = (curr - lastUpdateTick_) / 1000.0;
    lastUpdateTick_ = curr;

    // Update graphics

    if (curr - lastTick_ >= 1000 / animationSpeed_)
    {
        currFrame_ = (currFrame_ + 1) % 3;
        lastTick_ = curr;
    }

    // Update physics
    
    if (angle_ < 90)
    {
        angularVel_ += angularAcc_ * deltaTime_;
        angle_ += angularVel_ * deltaTime_;
    }
    if (angle_ < -45)
        angle_ = -45;

    velocityY_ += gravityScale_ * 9.8 * deltaTime_;
    y_ += velocityY_ * deltaTime_;
    if (y_ < 0)
        y_ = 0.0;
}

void Bird::step()
{
    angularVel_ = -70.0;
    angle_ = 0.0;
    velocityY_ = -200.0;
}

void Bird::render()
{
    SDL_Rect dest = {
        x_, (int)y_,
        34, 24
    };
    SDL_RenderCopyEx(renderer_, textures_[currFrame_], NULL, &dest, angle_, NULL, SDL_FLIP_NONE);
}

void Bird::setColor(const std::string& color)
{
    auto texture = TextureManager::get();
    std::string states[] = {
        "downflap", "midflap", "upflap"
    };
    for (int i = 0; i < 3; ++i)
        textures_[i] = texture->retrieve(color + "bird-" + states[i]);
}