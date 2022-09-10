#include "texture.h"
#include "background.h"

Background::Background()
{
    auto texture = TextureManager::get();
    texture_[0] = texture->retrieve("background-night");
    texture_[1] = texture->retrieve("background-day");
    lastTick_ = SDL_GetTicks();
}

bool Background::isDay() const
{
    return day_;
}

void Background::update()
{
    auto currTick = SDL_GetTicks();
    if (currTick - lastTick_ > 1000 * 60 * 3)
    {
        day_ = !day_;
        lastTick_ = currTick;
    }
}

void Background::render()
{
    SDL_RenderCopy(renderer_, texture_[day_], NULL, NULL);
}