/**
 * @file Game.h
 * @author cF-embedded (cf@embedded.pl)
 * @brief game class
 * @copyright Copyright (c) 2024
 *
 */
extern "C"
{
#include "platform_specific.h"
#include "priority.h"
}

#include "game.h"
#include "lcd.h"

/**
 * @brief Control whole reaciton time game
 *
 * @param params Task parameteres - unused.
 */
static void game_task(void* params);

void game_task_init(void)
{
    rtos_task_create(game_task, "game_task", GAME_TASK_STACKSIZE, GAME_TASK_PRIORITY, NULL);
}

Game::Game() : currentState(nullptr), Lcd(LCD_X_SIZE, LCD_Y_SIZE)
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

static void game_task(void* params)
{
    (void)params;
    tick_t tick_cnt;

    while(1)
    {
        tick_cnt = rtos_tick_count_get();

        rtos_delay_until(&tick_cnt, 100);
    }

    vTaskSuspend(NULL);
}