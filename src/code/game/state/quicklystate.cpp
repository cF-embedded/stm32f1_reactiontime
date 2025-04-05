/**
 * @file quicklystate.cpp
 * @author cF-embedded (cf@embedded.pl)
 * @brief implementation of quickly state
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
#include "quicklystate.h"

void QuicklyState::Enter(Game* game)
{
    game->Lcd.fillScreen(Color::RED);
    game->Lcd.drawString(50, 125, "Too quickly!", Color::BLACK, Color::RED, 2);
}

void QuicklyState::Update(Game* game)
{
    if(game->Lcd.isTouchScreenPressed())
    {
        game->ChangeState(new StartState());
    }
}

void QuicklyState::Exit(Game* game) {}
