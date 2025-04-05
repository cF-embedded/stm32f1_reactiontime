/**
 * @file game.h
 * @author cF-embedded (cf@embedded.pl)
 * @brief game class
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _GAME_H
#define _GAME_H

#include "gamestate.h"
#include "lcd.h"
#include "reactionstate.h"
#include "resultstate.h"
#include "startstate.h"
#include "waitingstate.h"

class Game
{
  public:
    LCD Lcd;
    Game();

    void ChangeState(GameState* state);

    void Enter();
    void Update();
    void Exit();

    GameState* currentState;
};

/**
 * @brief game task initialization.
 *
 * game task is responsible for controll whole game
 */
void game_task_init(void);

#endif   // _GAME_H
