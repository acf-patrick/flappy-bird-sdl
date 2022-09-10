#pragma once

#include <string>
#include <SDL2/SDL.h>

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void render();
    virtual void update();

protected:
    SDL_Renderer* renderer_ = nullptr;
};