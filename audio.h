#pragma once

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class AudioManager
{
public:
    static AudioManager* get();

    ~AudioManager();

    void load(const std::string& file, const std::string& tag);

    void play(const std::string& tag);

private:
    static AudioManager* instance_;

    std::map<std::string, Mix_Chunk*> chunks_;

    AudioManager();
};