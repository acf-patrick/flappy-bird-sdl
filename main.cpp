#include <iostream>

#include "game.h"

int main(int argc, char** argv)
{
    auto game = Game::get();

    game->run();

    delete game;

    return 0;
}