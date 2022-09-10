#include "group.h"
#include "object.h"

#include <iostream>

Group::Group()
{

}

Group::~Group()
{
    for (auto& [tag, object] : objects_)
        delete object;
    objects_.clear();
}

GameObject* Group::remove(const std::string& tag)
{
    auto object = objects_[tag];
    objects_.erase(tag);
    return object;
}

void Group::push(GameObject* object, const std::string& tag)
{
    if (objects_.find(tag) == objects_.end())
        orderedTags_.emplace_back(tag);
    objects_[tag] = object;
}

void Group::update()
{
    for (auto tag : orderedTags_)
        objects_[tag]->update();
}

void Group::render()
{
    for (auto tag : orderedTags_)
        objects_[tag]->render();
}

GameObject* Group::get(const std::string& tag)
{
    if (objects_.find(tag) == objects_.end())
        return nullptr;
    return objects_[tag];
}