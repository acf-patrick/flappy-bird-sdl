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

private:
    float animationSpeed_ = 6.0;
    Uint32 lastTick_;
    int currFrame_ = 0;

    bool idle_ = true;

    float deltaTime_ = 0.0;
    Uint32 lastUpdateTick_;

    int x_ = 50;

    float velocityY_ = 0.0;
    int startY_ = 200;
    float y_ = 200;

    float gravityScale_ = 40.0;
    
    float angularAcc_ = 100.0;
    float angularVel_ = 0.0;
    float angle_ = 0.0;

    SDL_Texture* textures_[3];
};