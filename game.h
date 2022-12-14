#pragma once

#include <deque>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

class Pipe;
class Base;
class Bird;
class GameObject;
class Background;
class AudioManager;
class TextureManager;

class Game 
{
    enum State
    {
        BEGIN,
        PLAYING,
        GAMEOVER
    };

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

    void loadScore();

    void createObjects();

    void log(const std::string& message);

    void manageEvents(const SDL_Event& event);

    void setState(State state);

    void update();

    void render();

    void dead();

    void score();

    void createPipes();

    void resetPipes();

    bool hasHitGround();

    void darkenScreen();

    void drawScore();

private:
    State state_ = BEGIN;

    bool sudo_ = false;

    bool running_ = true;

    bool dead_ = false;

    Pipe* lastPipeHead_ = nullptr;
    int score_ = 0;
    int maxScore_ = 0;

    Background* background_;
    Base* base_;
    Bird* bird_;
    std::deque<Pipe*> pipes_;

    std::vector<GameObject*> objects_;

    int pipeSpace_ = 100;

    /* window size */

    int width_ = 288;
    int height_ = 512;

    SDL_Window* window_;
    SDL_Renderer* renderer_;

    AudioManager* audios_;

    TextureManager* textures_;
};