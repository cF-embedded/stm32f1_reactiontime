/**
 * @file reactionstate.cpp
 * @author cF-embedded (cf@embedded.pl)
 * @brief implementation of reaction state
 *
 * @copyright Copyright (c) 2025
 *
 */

extern "C"
{
#include "platform_specific.h"
}

#include "game.h"
#include "lcd.h"
#include "reactionstate.h"

void ReactionState::Enter(Game* game)
{
    reactionTime = rtos_tick_count_get();
    game->Lcd.fillScreen(Color::GREEN);
    game->Lcd.drawString(50, 125, "GO! Tap now!", Color::BLACK, Color::GREEN, 2);
}

void ReactionState::Update(Game* game)
{
    if(game->Lcd.isTouchScreenPressed())
    {
        tick_t actTime = rtos_tick_count_get() - reactionTime;

        game->ChangeState(new ResultState(actTime));
    }
}

void ReactionState::Exit(Game* game) {}
