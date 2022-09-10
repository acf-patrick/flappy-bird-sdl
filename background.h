#pragma once

#include "object.h"

class Background : public GameObject
{
public:
    Background();

    bool isDay() const;

    void update() override;
    void render() override;

private:
    SDL_Texture* texture_[2];
    bool day_ = true;
    Uint32 lastTick_;
};