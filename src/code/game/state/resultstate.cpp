/**
 * @file resultstate.cpp
 * @author cF-embedded (cf@embedded.pl)
 * @brief implementation of result state
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "resultstate.h"
#include "game.h"

void ResultState::Enter(Game* game) {}

void ResultState::Update(Game* game)
{
    game->ChangeState(new StartState());
}

void ResultState::Exit(Game* game) {}
