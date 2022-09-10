#pragma once

#include <SDL2/SDL.h>

#include "object.h"

class Base : public GameObject
{
public:
    Base();

    void update() override;
    void render() override;

private:
    SDL_Texture* texture_ = nullptr;
    float x_ = 0;
    int width_;
    int height_;
};