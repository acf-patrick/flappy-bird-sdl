#include "audio.h"

#include <iostream>

AudioManager* AudioManager::instance_ = nullptr;

AudioManager* AudioManager::get()
{
    if (!instance_)
        instance_ = new AudioManager;
    return instance_;
}

AudioManager::AudioManager()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 0x400) < 0)
    {
        std::cerr << "SDL mixer error : " << Mix_GetError() << std::endl;
        exit(1);
    }
}

AudioManager::~AudioManager()
{   
    for (auto [ tag, chunk ] : chunks_)
        Mix_FreeChunk(chunk);

    Mix_CloseAudio();
}

void AudioManager::load(const std::string& file, const std::string& tag)
{
    auto sound = Mix_LoadWAV(file.c_str());
    if (!sound)
    {
        std::cerr << "Failed to load" << file << std::endl;
        return;
    }

    chunks_[tag] = sound;
}

void AudioManager::play(const std::string& tag)
{
    if (chunks_.find(tag) == chunks_.end())
        return;
    Mix_PlayChannel(-1, chunks_[tag], 1);
}