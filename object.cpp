#include "object.h"

#include "game.h"

GameObject::GameObject()
{
    renderer_ = Game::get()->getRenderer();
}

GameObject::~GameObject()
{
    // override
}

void GameObject::update()
{
    // override
}

void GameObject::render()
{
    // override
}