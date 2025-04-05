/**
 * @file resultstate.h
 * @author cF-embedded (cf@embedded.pl)
 * @brief result state definition file
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _RESULTSTATE_H
#define _RESULTSTATE_H

extern "C"
{
#include "platform_specific.h"
}

#include "gamestate.h"

class ResultState : public GameState
{
  public:
    ResultState(tick_t reactionTime);
    void Enter(Game* game) override;
    void Update(Game* game) override;
    void Exit(Game* game) override;

  private:
    tick_t _reactionTime;
};

#endif   // _RESULTSTATE_H
