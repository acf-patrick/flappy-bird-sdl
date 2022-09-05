#include <iostream>
#include <SDL2/SDL_image.h>

#include "game.h"
#include "texture.h"

TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager()
{
    instance = this;
}

TextureManager::~TextureManager()
{
    for (auto& [tag, texture] : textures_)
        SDL_DestroyTexture(texture);
    textures_.clear();

    instance = nullptr;
}

TextureManager* TextureManager::get()
{
    if (!instance)
        new TextureManager;
    return instance;
}

SDL_Texture* TextureManager::load(const std::string& path, const std::string& tag)
{
    auto& texture = textures_[tag];
    if (texture)
        return texture;

    texture = IMG_LoadTexture(Game::get()->getRenderer(), path.c_str());
    if (!texture)
        std::cerr << "Failed to load " << path << std::endl;
        
    return texture;
}

SDL_Texture* TextureManager::retrieve(const std::string& tag)
{
    if (textures_.find(tag) == textures_.end())
    {
        std::cerr << tag << " : texture not loaded." << std::endl;
        return nullptr;
    }
    return textures_[tag];
}