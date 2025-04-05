/**
 * @file reactionstate.cpp
 * @author cF-embedded (cf@embedded.pl)
 * @brief implementation of reaction state
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "reactionstate.h"
#include "game.h"

void ReactionState::Enter(Game* game)
{
}

void ReactionState::Update(Game* game)
{
    game->ChangeState(new ResultState());
}

void ReactionState::Exit(Game* game) {}
