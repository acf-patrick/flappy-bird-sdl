#pragma once

#include <map>
#include <string>
#include <SDL2/SDL.h>

class TextureManager
{
public:
    ~TextureManager();

    static TextureManager* get();

    SDL_Texture* load(const std::string& path, const std::string& tag);
    SDL_Texture* retrieve(const std::string& tag);

private:
    static TextureManager* instance;

    TextureManager();
    
    SDL_Renderer* renderer_;

    std::map<std::string, SDL_Texture*> textures_;
};