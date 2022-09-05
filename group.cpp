#include "group.h"
#include "object.h"

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
    objects_[tag] = object;
}

void Group::update()
{
    for (auto& [tag, object] : objects_)
        objects_[tag]->update();
}

void Group::render()
{
    for (auto& [tag, object] : objects_)
        objects_[tag]->render();
}