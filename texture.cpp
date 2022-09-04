#include <iostream>
#include <SDL2/SDL_image.h>

#include "game.h"
#include "texture.h"

TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager()
{
    renderer_ = Game::get()->getRenderer();
}

TextureManager::~TextureManager()
{
    instance = nullptr;
}

TextureManager* TextureManager::get()
{
    if (!instance)
        instance = new TextureManager;
    return instance;
}

SDL_Texture* TextureManager::load(const std::string& path, const std::string& tag)
{
    auto t = IMG_LoadTexture(renderer_, path.c_str());
    if (!t)
        std::cerr << "Failed to load " << path << std::endl;
    else
        textures_[tag] = t;
    return t;
}

SDL_Texture* TextureManager::retrieve(const std::string& tag)
{
    return textures_[tag];
}