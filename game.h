#pragma once

#include <deque>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

class Pipe;
class Base;
class GameObject;
class Background;
class TextureManager;

class Game 
{
public:
    static Game* get();

    ~Game();

    void run();

    SDL_Renderer* getRenderer();

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

    void createPipes();

private:
    bool running = true;

    Background* background_;
    Base* base_;
    std::deque<Pipe*> pipes_;

    std::vector<GameObject*> objects_;

    int pipeSpace_ = 80;

    /* window size */

    int width_ = 288;
    int height_ = 512;

    SDL_Window* window_;
    SDL_Renderer* renderer_;

    TextureManager* textures_;
};