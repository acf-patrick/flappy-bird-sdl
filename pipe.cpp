#include "pipe.h"
#include "game.h"
#include "texture.h"

#include <vector>
#include <cstdlib>
#include <iostream>

int randint(int min, int max)
{
    auto p = rand() / (float)RAND_MAX;
    return min + p * (max - min);
}

Pipe::Pipe(const std::string& color)
{
    auto wSize = Game::get()->getWindowSize();    
    auto texture = TextureManager::get();
    texture_ = texture->retrieve("pipe-" + color);
    SDL_QueryTexture(texture_, NULL, NULL, &tSize_.x, &tSize_.y);
    x_ = wSize.x;
    y_ = randint(gap_ + 20, wSize.y - 112 - 20);

    lastTick_ = SDL_GetTicks();
}

void Pipe::render()
{
    SDL_Rect dest { int(x_), int(y_), tSize_.x, tSize_.y };
    SDL_RenderCopy(renderer_, texture_, NULL, &dest);

    dest = { int(x_), int(y_ - gap_ - tSize_.y), tSize_.x, tSize_.y };
    SDL_RenderCopyEx(renderer_, texture_, NULL, &dest, 180, NULL, SDL_FLIP_NONE);
}

void Pipe::update()
{
    auto curr = SDL_GetTicks();
    deltaTime_ = (curr - lastTick_) / 1000.0;
    lastTick_ = curr;

    x_ += speed_ * deltaTime_;
}

bool Pipe::isOut() const
{
    return getRight() < 0;
}

int Pipe::getRight() const
{
    return x_ + tSize_.x;
}

bool Pipe::collide(const SDL_Rect& rect)
{
    SDL_Rect rects[2] = {
        { int(x_), int(y_ - gap_ - tSize_.y), tSize_.x, tSize_.y },
        { int(x_), int(y_), tSize_.x, tSize_.y }
    };
    return SDL_IntersectRect(&rects[0], &rect, NULL) || SDL_IntersectRect(&rects[1], &rect, NULL);
}