/**
 * @file waitingstate.cpp
 * @author cF-embedded (cf@embedded.pl)
 * @brief implementation of waiting state
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
#include "waitingstate.h"

bool WaitingState::isTimeElapsed(tick_t time)
{
    return (time >= waitingTime);
}

void WaitingState::Enter(Game* game)
{
    game->Lcd.fillScreen(Color::RED);
    game->Lcd.drawString(20, 125, "Stay sharp... the signal is coming!", Color::BLACK, Color::RED, 1);
    srand(static_cast<unsigned int>(rtos_tick_count_get()));
    waitingTime = static_cast<tick_t>(1000 + (rand() % 5001)) + rtos_tick_count_get();
}

void WaitingState::Update(Game* game)
{
    tick_t actTime = rtos_tick_count_get();

    if(isTimeElapsed(actTime))
    {
        game->ChangeState(new ReactionState());
    }
}

void WaitingState::Exit(Game* game) {}
