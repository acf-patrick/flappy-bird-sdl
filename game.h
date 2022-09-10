#pragma once

#include <string>
#include <SDL2/SDL.h>

#include "group.h"
#include "texture.h"

class Game 
{
public:
    static Game* get();

    ~Game();

    void run();

    SDL_Renderer* getRenderer();

    GameObject* getObject(const std::string& tag);

    SDL_Point getWindowSize();

private:
    static Game* instance;

    Game();

    void loadAssets();

    void createObjects();

    void log(const std::string& message);

    void manageEvents(const SDL_Event& event);

    void update();

    void render();

private:
    bool running = true;

    /* window size */

    int width_ = 288;
    int height_ = 512;

    SDL_Window* window_;
    SDL_Renderer* renderer_;

    TextureManager* textures_;

    Group objects_;
};