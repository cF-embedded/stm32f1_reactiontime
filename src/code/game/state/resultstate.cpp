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
#include "lcd.h"
#include "string.h"

ResultState::ResultState(tick_t reactionTime) : _reactionTime(reactionTime) {}

void ResultState::Enter(Game* game)
{
    game->Lcd.fillScreen(Color::CYAN);
    game->Lcd.drawString(70, 125, std::to_string(_reactionTime) + " ms", Color::BLACK, Color::CYAN, 2);
}

void ResultState::Update(Game* game)
{
    if(game->Lcd.isTouchScreenPressed())
    {
        game->ChangeState(new StartState());
    }
}

void ResultState::Exit(Game* game) {}
