/**
 * @file Game.h
 * @author cF-embedded (cf@embedded.pl)
 * @brief game class
 * @copyright Copyright (c) 2024
 *
 */

#include "game.h"

Game::Game() : currentState(nullptr)
{
    ChangeState(new StartState());
}

void Game::ChangeState(GameState* state)
{
    if(currentState != nullptr)
    {
        currentState->Exit(this);
    }

    currentState = state;
    currentState->Enter(this);
}

void Game::Enter()
{
    if(currentState != nullptr)
    {
        currentState->Enter(this);
    }
}

void Game::Update()
{
    if(currentState != nullptr)
    {
        currentState->Update(this);
    }
}

void Game::Exit()
{
    if(currentState != nullptr)
    {
        currentState->Exit(this);
    }
}