#pragma once

#include <string>

#include "object.h"

class Pipe : public GameObject
{
public:
    Pipe(const std::string& color);

    ~Pipe() = default;

    void update() override;
    void render() override;

    bool isOut() const;
    bool collide(const SDL_Rect& rect);

    int getRight() const;

private:
    float deltaTime_;
    Uint32 lastTick_;

    int gap_ = 100;
    float speed_ = -60.0;

    float x_, y_;

    SDL_Point tSize_;
    SDL_Texture* texture_;
};