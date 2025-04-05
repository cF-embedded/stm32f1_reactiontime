/**
 * @file quicklystate.h
 * @author cF-embedded (cf@embedded.pl)
 * @brief quickly state definitions file
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _QUICKLYSTATE_H
#define _QUICKLYSTATE_H

extern "C"
{
#include "platform_specific.h"
}

#include "gamestate.h"

class QuicklyState : public GameState
{
  public:
    void Enter(Game* game) override;
    void Update(Game* game) override;
    void Exit(Game* game) override;
};

#endif   // _QUICKLYSTATE_H
