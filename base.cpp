#include "base.h"
#include "game.h"
#include "texture.h"

Base::Base()
{
    auto texture = TextureManager::get();
    texture_ = texture->retrieve("base");
    SDL_QueryTexture(texture_, NULL, NULL, &width_, &height_);
}

void Base::update()
{
    x_ -= 0.05;
    if (x_ <= -width_)
        x_ = 0;
}

void Base::render()
{
    auto game = Game::get();
    SDL_Rect dest = {
        (int)x_, game->getWindowSize().y - height_,
        width_, height_
    };

    SDL_RenderCopy(game->getRenderer(), texture_, NULL, &dest);

    dest.x += width_;
    SDL_RenderCopy(game->getRenderer(), texture_, NULL, &dest);
}