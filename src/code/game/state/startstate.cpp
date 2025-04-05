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
#include "lcd.h"

void StartState::Enter(Game* game)
{
    game->Lcd.fillScreen(Color::BLACK);
    game->Lcd.fillScreen(Color::CYAN);
    game->Lcd.drawString(40, 125, "Ready to test your reflexes?", Color::BLACK, Color::CYAN, 1);
    game->Lcd.drawString(45, 145, "Touch the screen to start!", Color::BLACK, Color::CYAN, 1);
}

void StartState::Update(Game* game)
{
    if(game->Lcd.isTouchScreenPressed())
    {
        game->Lcd.fillScreen(Color::CYAN);
        game->ChangeState(new WaitingState());
    }
}

void StartState::Exit(Game* game)
{
    game->Lcd.fillScreen(Color::RED);
}
