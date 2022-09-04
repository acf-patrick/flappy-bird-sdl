#pragma once

#include <string>
#include <SDL2/SDL.h>

class Game 
{
public:
    static Game* get();

    ~Game();

    void run();

    SDL_Renderer* getRenderer();

private:
    static Game* instance;

    Game();

    void log(const std::string& message);

    /* window size */

    int width = 288;
    int height = 512;

    SDL_Window* window_;
    SDL_Renderer* renderer_;
};