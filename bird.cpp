#include "bird.h"
#include "texture.h"

Bird::Bird(const std::string& color)
{
    setColor(color);
}

void Bird::update()
{
    auto curr = SDL_GetTicks();
    if (curr - lastTick_ >= 1000 / animationSpeed_)
    {
        currFrame_ = (currFrame_ + 1) % 3;
        lastTick_ = curr;
    }
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