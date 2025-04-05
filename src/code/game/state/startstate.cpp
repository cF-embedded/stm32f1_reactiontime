/**
 * @file startstate.cpp
 * @author cF-embedded (cf@embedded.pl)
 * @brief implementation of start state
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "startstate.h"
#include "game.h"

void StartState::Enter(Game* game) {}

void StartState::Update(Game* game)
{
    game->ChangeState(new WaitingState());
}

void StartState::Exit(Game* game) {}
