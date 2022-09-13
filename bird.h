#pragma once

#include "object.h"

#include <map>
#include <string>

class Bird : public GameObject
{
public:
    Bird(const std::string& color);

    void setColor(const std::string& color);

    void step();

    void update() override;
    void render() override;

    SDL_Rect getRect() const;

    void toggleState();

    void reset();

private:
    float animationSpeed_ = 6.0;
    Uint32 lastTick_;
    int currFrame_ = 0;

    bool idle_ = true;

    float deltaTime_ = 0.0;
    Uint32 lastUpdateTick_;

    int x_ = 50;

    float velocityY_;

    int startY_ = 200;
    float y_;

    float gravityScale_ = 40.0;
    
    float angularAcc_;
    float angularVel_;
    float angle_;

    SDL_Texture* textures_[3];
};