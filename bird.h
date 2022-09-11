#pragma once

#include "object.h"

#include <map>
#include <string>

class Bird : public GameObject
{
public:
    Bird(const std::string& color);

    void setColor(const std::string& color);

    void update() override;
    void render() override;

private:
    float animationSpeed_ = 4.0;
    Uint32 lastTick_;
    int currFrame_ = 0;

    int x_ = 50;
    float y_ = 100;
    float angle_ = 0.0;

    SDL_Texture* textures_[3];
};