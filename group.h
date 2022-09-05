#pragma once

#include <map>
#include <string>
#include <SDL2/SDL.h>

class GameObject;

class Group
{
public:
    Group();
    ~Group();

    GameObject* remove(const std::string& tag);

    GameObject* get(const std::string& tag);

    void push(GameObject* object, const std::string& tag);

    void update();

    void render();

private:
    std::map<std::string, GameObject*> objects_;
};